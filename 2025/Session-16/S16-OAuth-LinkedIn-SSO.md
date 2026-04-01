https://itnext.io/fastapi-linkedin-single-sign-on-sso-b1a0118b02d7



## FastAPI: LinkedIn Single Sign-On (SSO)

### Effortless user onboarding in FastAPI app via LinkedIn Single-Sign-On

![Image by author](../assets/1_qtGya7tSHK9qOBMfpbI0aQ.webp)

## What SSO stands for?

[Single Sign-On (SSO)](https://aigents.co/learn?search=SSO) is a convenient and secure authentication method that allows users to access multiple applications and services with a single set of login credentials. Instead of remembering and entering separate usernames and passwords for each application, SSO streamlines the process by providing a centralized login system. This not only enhances user experience but also improves security by reducing the risk of password-related vulnerabilities. Various SSO providers have emerged to cater to the increasing demand for streamlined access management.

## Goal

In this article, we will demonstrate a Single Sign-On implementation in FastAPI to login users in a system via **LinkedIn** **sign-in**.
>  For the equivalent processes with other providers you can follow those links to articles of this series:
>  *1. [*Facebook SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-facebook-single-sign-on-sso-b10865535029)
>  *2. [Microsoft SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-microsoft-single-sign-on-sso-d0a0ab248c36)*
>  *3. [Spotify SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-spotify-single-sign-on-sso-4f461b95344c)*
>  *4*. [Google SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-google-single-sign-on-sso-47454e2e2859)
>  5. [GitHub SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-github-single-sign-on-sso-f6b942395649)
>  6. [X (Twitter) SSO in FastAPI](https://medium.com/itnext/fastapi-x-twitter-single-sign-on-sso-5725671ad180)
>  7. [GitLab SSO in FastAPI](https://medium.com/gitconnected/fastapi-gitlab-single-sign-on-sso-624fe442ec56)

## Implementation
>  All of this article’s pieces of code are included in a dedicated GitHub [repository](https://github.com/chrisK824/fastapi-sso-example) that can be cloned/forked to test out the code or use it for one of your projects!
>  If you find it useful please leave it a star and share with anyone who might be interested!
>  🚀 **Live demo** at [https://fastapi-sso-example.vercel.app/](https://fastapi-sso-example.vercel.app/)

### Application

Our demonstration example will include a simple FastAPI application with just a minimal User Interface written in Jinja templates and Sqlite3 local storage for the users of the system. The user interface will present login methods to the user and a home page, after login, that will present some minimal counters for the users that have signed up in the application for each different provider of authentication.

### FastAPI authentication

In our demonstration we will use FastAPI with basic credentials and cookie authentication. Along with the basic credentials traditional login form, a user will have also the option to sign in with LinkedIn and other methods.

### FastAPI SSO

FastAPI SSO is an [open-source library](https://github.com/tomasvotava/fastapi-sso) that normalises the SSO process across some of the most popular providers and makes it easy for the developer to integrate easily the sign-in process.

I’m sure more ways must exist out there but I found that repository exposing the functionality simply enough and straight forward.

### LinkedIn app setup

In order to use the LinkedIn Single Sign-On mechanism, an app is needed to be created using the LinkedIn developers’ platform. Let’s follow the steps together:

* Navigate to https://www.linkedin.com/developers/apps and press the “Create app” button to start the process.

![Screenshot by author](../assets/1_3e00UaP77RrHT2C9-K3Vuw.webp)

* Give a name to your app and upload an app logo. An app also requires a LinkedIn Company page. For my demo purpose, since I do not want to create a LinkedIn page right now, I will use one of the test company pages as described in [documentation here](https://learn.microsoft.com/en-us/linkedin/marketing/community-management/organizations?view=li-lms-2024-03#test-organizations).

![Screenshot by author](../assets/1_Rxy8eiguJU9jd7hNg3MgXw.webp)

* Hit the create app button. The app has been created.

* Navigate to “Auth” tab. From that summary note down the “Client ID” and the “Primary Client Secret”. Those are the OAuth 2 Client ID and Secret respectively. We will use those credentials in a bit in our code configuration.

* In that step you also need to define a redirect URI. This URI is the target URL endpoint where the LinkedIn sign-in mechanism will redirect at, after its own authentication is done, passing along the user’s information. Notice that I’m using a localhost URI here. That’s because, I’ll try all that locally, since I’m not going to deploy that implementation on some host. Once and if your code is deployed on some server, then this URL should be updated to point to the exact IP/Domain and URL path for your callback endpoint.

![Screenshot by author](../assets/1_KzQMFrmQrloblL5egDFMNQ.webp)

* Navigate to **Products **tab of the app and locate the “Sign In with LinkedIn using OpenID Connect” element. Hit “Request access” button, accept the terms and proceed.

![Screenshot by author](../assets/1_2k9ZKRCvqwmeWoipxtMOBQ.webp)

* After the process has finished, navigate back to the **Auth **tab and refresh your page. The necessary scopes must be now present in the “OAuth 2.0 scopes” section of the app summary.

![Screenshot by author](../assets/1_N1qEST7bEYp5UtKrcIXO9w.webp)

### User interface

Our minimal user interface looks like this:

![Screenshot by author](../assets/1_KxIbC_hHiSWhqAjD6yavFw.webp)

Nothing fancy here, just a form where a user can log in and some different methods to sign-in.

The user interface implementation is done via Jinja template. Of course, any frontend framework can be used to separate the frontend implementation but all that are out of scope for this demo.

All we need to know about that user interface, is what happens when we click the LinkedIn sign-in button which is described by this piece of HTML code:

    <form class="col-lg-3" method="get" action="/v1/linkedin/login" style="text-align: center;">
        <button class="login-btn" type="submit"><i class="fa-brands fa-linkedin"></i></button>
    </form>

So, upon that button press (submit), the action that will be performed is to issue a GET request at relative path /v1/linkedin/login*. *Let’s keep that in mind and see what that means for our API endpoints in a bit.

### API endpoints

Our necessary endpoints for this process to work are looking like that:

    from fastapi import APIRouter, Depends, HTTPException, status
    from fastapi.responses import RedirectResponse
    from database_crud import users_db_crud as db_crud
    from schemas import UserSignUp
    from sqlalchemy.orm import Session
    from database import get_db
    from fastapi_sso.sso.linkedin import LinkedInSSO
    from starlette.requests import Request
    from authentication import create_access_token, SESSION_COOKIE_NAME
    from dotenv import load_dotenv
    from pathlib import Path
    import os
    
    
    directory_path = Path(__file__).parent
    env_file_path = directory_path.parent / '.env'
    
    load_dotenv()
    LINKEDIN_CLIENT_ID = os.getenv("LINKEDIN_CLIENT_ID")
    LINKEDIN_CLIENT_SECRET = os.getenv("LINKEDIN_CLIENT_SECRET")
    
    os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'
    
    linkedin_sso = LinkedInSSO(
        LINKEDIN_CLIENT_ID,
        LINKEDIN_CLIENT_SECRET,
        "http://localhost:9999/v1/linkedin/callback",
        allow_insecure_http=True
    )
    
    router = APIRouter(prefix="/v1/linkedin")
    
    
    @router.get("/login", tags=['LinkedIn SSO'])
    async def linkedin_login():
        with linkedin_sso:
            return await linkedin_sso.get_login_redirect()
    
    
    @router.get("/callback", tags=['LinkedIn SSO'])
    async def linkedin_callback(request: Request, db: Session = Depends(get_db)):
        """Process login response from LinkedIn and return user info"""
    
        try:
            with linkedin_sso:
                user = await linkedin_sso.verify_and_process(request)
            username = user.email if user.email else user.display_name
            user_stored = db_crud.get_user(db, username, user.provider)
            if not user_stored:
                user_to_add = UserSignUp(
                    username=username,
                    fullname=user.display_name
                )
                user_stored = db_crud.add_user(
                    db,
                    user_to_add,
                    provider=user.provider
                )
            access_token = create_access_token(
                username=user_stored.username,
                provider=user.provider
            )
            response = RedirectResponse(url="/", status_code=status.HTTP_302_FOUND)
            response.set_cookie(SESSION_COOKIE_NAME, access_token)
            return response
        except db_crud.DuplicateError as e:
            raise HTTPException(status_code=403, detail=f"{e}")
        except ValueError as e:
            raise HTTPException(status_code=400, detail=f"{e}")
        except Exception as e:
            raise HTTPException(
                status_code=500,
                detail=f"An unexpected error occurred. Report this message to support: {e}"
            )

Let’s see what happens here:

* The environment variables loaded are the LinkedIn Client ID and secret, the ones we received after setting up our LinkedIn app in the developer’s portal.

* The LinkedInSSO class is included in the imported SSO library that we talked a bit earlier. Notice that during instatiation we need to provide our LinkedIn app credentials there, as well as our redirect URL, same as callback URL declared in our LinkedIn app. Additionally, since we need to test this locally and without any https protocol enabled, we need to declare that and allow insecure http traffic by setting the related argument to True.

* The /v1/linkedin/loginendpoint is where the whole mechanism is triggered by. Remember that was the route that our LinkedIn sign-in button was targetting upon in our form. The function executed calls the get_login_redirect method of the linkedin_ssoinstance which triggers the LinkedIn sign-in flow in our browser.

## Signing-in in via the User Interface

Let’s trigger the log in process using the LinkedIn button in our User Interface. This will redirect us here:

![Screenshot by author](../assets/1_Jr9MzlP_sFftvs81Rmdlcw.webp)

* The sign-in flow goes through the usual user-password authentication and includes any additional security rules like 2FA via phone etc.

* Notice that the form window declares our LinkedIn app name, the one created in LinkedIn developers’ platform.

![Screenshot by author](../assets/1_kR5ZUFoykUfJbHX4FBKpjA.webp)

* Once the LinkedIn sign-in process is finished, the LinkedIn app will redirect to our declared redirect URI, hence [http://localhost:9999/v1/linkedin/callback](http://localhost:9999/v1/google/callback) which takes us back into our local application and the second endpoint in our code.

* All user’s information is received in *user* object in this line

    user = await linkedin_sso.verify_and_process(request)

**After this point you can do whatever you want with that information for that user.**

* Personally, in this implementation, I chose to store the user’s email in my database as username for my user model and proceed by signing that user in the API. The chosen method here is to create a JWT token and set it as a cookie in the response. That way the user will remain signed-in while in browser and the function will finish its execution by redirecting the user to the home page at root / path where the Jinja template that is rendered recognises the user information received.

![Screenshot by author](../assets/1_Gt4TQBVSxWEVPZLMeFLy5g.webp)

The username displayed is the LinkedIn username received from the LinkedIn SSO mechanism and the table presented are just stats from the local database. Notice that LinkedIn provider has authenticated one user so far.
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
