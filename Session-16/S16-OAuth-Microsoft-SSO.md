
https://itnext.io/fastapi-microsoft-single-sign-on-sso-d0a0ab248c36

## FastAPI: Microsoft Single Sign-On (SSO)

![Image by author](../assets/1_-PX5t_mz1CjIMPedOpf4jQ.webp)

## What SSO stands for?

Single Sign-On (SSO) is a convenient and secure authentication method that allows users to access multiple applications and services with a single set of login credentials. Instead of remembering and entering separate usernames and passwords for each application, SSO streamlines the process by providing a centralized login system. This not only enhances user experience but also improves security by reducing the risk of password-related vulnerabilities. Various SSO providers have emerged to cater to the increasing demand for streamlined access management.

## Goal

In this article, we will demonstrate a Single Sign-On implementation in FastAPI to login users in a system via **Microsoft Sign-in**.
>  For the equivalent processes with other providers you can follow those links to articles of this series:
>  *1. [*Facebook SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-facebook-single-sign-on-sso-b10865535029)
>  *2. [GitHub SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-github-single-sign-on-sso-f6b942395649)*
>  *3. [Spotify SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-spotify-single-sign-on-sso-4f461b95344c)*
>  *4*. [Google SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-google-single-sign-on-sso-47454e2e2859)
>  5. [LinkedIn SSO in FastAPI](https://itnext.io/fastapi-linkedin-single-sign-on-sso-b1a0118b02d7)
>  6. [X (Twitter) SSO in FastAPI](https://medium.com/itnext/fastapi-x-twitter-single-sign-on-sso-5725671ad180)
>  7. [GitLab SSO in FastAPI](https://medium.com/gitconnected/fastapi-gitlab-single-sign-on-sso-624fe442ec56)

## Implementation
>  All of this article’s pieces of code are included in a dedicated GitHub [repository](https://github.com/chrisK824/fastapi-sso-example) that can be cloned/forked to test out the code or use it for one of your projects!
>  If you find it useful please leave it a star and share with anyone who might be interested!
>  🚀 **Live demo** at [https://fastapi-sso-example.vercel.app/](https://fastapi-sso-example.vercel.app/)

### Application

Our demonstration example will include a simple FastAPI application with just a minimal User Interface written in Jinja templates and Sqlite3 local storage for the users of the system. The user interface will present login methods to the user and a home page, after login, that will present some minimal counters for the users that have signed up in the application for each different provider of authentication.

### FastAPI authentication

In our demonstration we will use FastAPI with basic credentials and cookie authentication. Along with the basic credentials traditional login form, a user will have also the option to sign in with Microsoft and other methods.

### FastAPI SSO

FastAPI SSO is an [open-source library](https://github.com/tomasvotava/fastapi-sso) that normalises the SSO process across some of the most popular providers and makes it easy for the developer to integrate easily the sign-in process.

I’m sure more ways must exist out there but I found that repository exposing the functionality simply enough and straight forward.

### Microsoft app setup

In order to use the Microsoft Single Sign-On mechanism, an app is needed to be registered using the Microsoft Azure Portal , let’s follow the steps together:

* Firstly, one will need a Microsoft account and an Azure account setup. So in order to perform the next steps you need to setup your account and access Microsoft Azure Portal. Do not worry about billing, as nothing in this demo is billable.

* While in Google Cloud console, search in the search bar for “App registrations”.

![](../assets/1_3QF83jRhNe-VQiJr9mMGPg.webp)

* Name your application and select the third option in the access configuration (I chose the broader configuration I could see there, but feel free to explore based on your needs). Next, add a redirect URI. This URI is the callback endpoint where the Microsoft sign-in mechanism will redirect at, after its own authentication is done, passing along the user’s information. Notice that I’m using a localhost URI here. That’s because, I’ll try all that locally, since I’m not going to deploy that implementation on some host. Once and if your code is deployed on some server, then this URI should be updated to point to the exact IP/Domain and URI path for your callback endpoint.

![](../assets/1_N-2t4mFnt9K31BkQ7_w_Eg.webp)

* Press “Register”. When registration is finished this screen will pop up.

![](../assets/1_N3HQi5lxkIKAk17gwbbTjw.webp)

Just below the “Client credentials” section, click the link to create a secret for your application.

Make sure to note down the Application (client) ID and secret values as well as the Directory (tenant) ID. Will use those later in our code configuration.

* Finally navigate to “API permissions” and configure the following permissions for your registered app:

![](../assets/1_32V1_VEYxN6UQvWvSZiMlg.webp)

### User interface

Our minimal user interface looks like this:

![](../assets/1_ifrxuJd2-RD7fGiQ6jpcdw.webp)

Nothing fancy here, just a form where a user can log in and some different methods to sign-in.

The user interface implementation is done via Jinja template. Of course, any frontend framework can be used to separate the frontend implementation but all that are out of scope for this demo.

All we need to know about that user interface, is what happens when we click the Google sign-in button which is described by this piece of HTML code:

    <form class="col-lg-2" method="get" action="/v1/microsoft/login" style="text-align: center;">
        <button class="login-btn" type="submit">
            <i class="fa-brands fa-microsoft"></i>
        </button>
    </form>

So, upon that button press (submit), the action that will be performed is to issue a GETrequest at relative path /v1/microsoft/login*. *Let’s keep that in mind and see what that means for our API endpoints in a bit.

### API endpoints

Our necessary endpoints for this process to work are looking like that:

    from fastapi import APIRouter, Depends, HTTPException, status
    from fastapi.responses import RedirectResponse
    from database_crud import users_db_crud as db_crud
    from schemas import UserSignUp
    from sqlalchemy.orm import Session
    from database import get_db
    from fastapi_sso.sso.microsoft import MicrosoftSSO
    from starlette.requests import Request
    from authentication import create_access_token, SESSION_COOKIE_NAME
    from dotenv import load_dotenv
    from pathlib import Path
    import os
    
    
    directory_path = Path(__file__).parent
    env_file_path = directory_path.parent / '.env'
    
    load_dotenv()
    MICROSOFT_CLIENT_ID =  os.getenv("MICROSOFT_CLIENT_ID")
    MICROSOFT_CLIENT_SECRET =  os.getenv("MICROSOFT_CLIENT_SECRET")
    TENANT =  os.getenv("TENANT")
    
    os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'
    
    microsoft_sso = MicrosoftSSO(
        MICROSOFT_CLIENT_ID,
        MICROSOFT_CLIENT_SECRET,
        "http://localhost:9999/v1/microsoft/callback",
        allow_insecure_http=True,
        tenant=TENANT
    )
    
    router = APIRouter(prefix="/v1/microsoft")
    
    
    @router.get("/login", tags=['Microsoft SSO'])
    async def microsoft_login():
        return await microsoft_sso.get_login_redirect()
    
    
    @router.get("/callback", tags=['Microsoft SSO'])
    async def microsoft_callback(request: Request, db: Session = Depends(get_db)):
        """Process login response from Microsoft and return user info"""
    
        try:
            user = await microsoft_sso.verify_and_process(request)
            user_stored = db_crud.get_user(db, user.email, user.provider)
            if not user_stored:
                user_to_add = UserSignUp(
                    username=user.email if user.email else user.display_name,
                    fullname=user.display_name
                )
                user_stored = db_crud.add_user(db, user_to_add, provider=user.provider)
            access_token = create_access_token(username=user_stored.username, provider=user.provider)
            response = RedirectResponse(url="/", status_code=status.HTTP_302_FOUND)
            response.set_cookie(SESSION_COOKIE_NAME, access_token)
            return response
        except db_crud.DuplicateError as e:
            raise HTTPException(status_code=403, detail=f"{e}")
        except ValueError as e:
            raise HTTPException(status_code=400, detail=f"{e}")
        except Exception as e:
            raise HTTPException(
                status_code=500, detail=f"An unexpected error occurred. Report this message to support: {e}")

Let’s see what happens here:

* The environment variables loaded are the Microsoft Client ID and secret, as well as the tenant ID. We received all of those after registering our Microsoft app and credentials in Microsoft Azure Portal.

* The MicrosoftSSO class is included in the imported SSO library that we talked a bit earlier. Notice that during instatiation we need to provide our app credentials there, as well as our redirect URI, same as the redirect URI declared in our Google app. Additionally, since we need to test this locally and without any https protocol enabled, we need to declare that and allow insecure http traffic by setting the related argument to True.

* The /v1/microsoft/loginendpoint is where the whole mechanism is triggered by. Remember that was the route that our Microsoft sign-in button was targetting upon in our user interface form. The function executed calls the get_login_redirect method of the microsoft_sso instance which triggers the Microsoft sign-in flow in our browser.

* The sign-in flow goes through the usual user-password authentication and includes any additional security rules like 2FA via phone etc.

![](../assets/1_S478UN3dNKWqCjipKcehkQ.webp)

* If the application is not further configurated, just like this demo here, then a warning may pop up in the process:

![](../assets/1_SFcDWrFb1mqSc8WQ27tj5A.webp)

* I’m just pressing continue for the sake of this demo.

* Once the Google sign-in process is finished, the Google app will redirect to our declared redirect URI, hence [http://localhost:9999/v1/google/callback](http://localhost:9999/v1/google/callback) which takes us back into our local FastAPI application and specifically to the second endpoint in our code.

* All user’s information is received in *user* object in this line

    user = await google_sso.verify_and_process(request)

**After this point you can do whatever you want with that information for that user.**

* Personally, in this implementation, I chose to store the user’s email in my database as username for my user model and proceed by signing that user in the API. The chosen method here is to create a JWT token and set it as a cookie in the response. That way the user will remain signed-in while in browser and the function will finish its execution by redirecting the user to the home page at root / path where the Jinja template that is rendered recognises the user information received.

![](../assets/1_xd47duAYGBs-EBSE5xd57A.webp)

The username displayed is the email received from the Google SSO mechanism and the table presented are just statistics from the local database. Notice that Google provider has authenticated one user so far.
>  That’s all folks!
>  Thank you for taking the time to read through to the end — I truly hope you found this article valuable!

## How to support me

If you found this article useful consider showing your appreciation by:

* 👏 Leaving a round of applause

* ✍️ Sharing your feedback in the comments section below

* 🤌 Highlighting your favourite parts

* 📣 Sharing it with whoever might be interested

Like what you read and want more?

* 👉 Hit the follow button and stay updated on future posts!

* 🔔 Subscribe to get an email whenever a new story of mine is out!

* 🔗 Follow me: [GitHub](https://github.com/chrisK824) | [LinkedIn](https://www.linkedin.com/in/chriskarvouniaris) | [X](https://x.com/ChrisKarvou247?)

☕ [Enjoyed this piece? Consider buying me a coffee to support future content creation and help keep the coffee flowing!](https://ko-fi.com/chriskarvouniaris)
>  Until next time, happy reading and coding!
