https://itnext.io/fastapi-x-twitter-single-sign-on-sso-5725671ad180


## FastAPI: X(Twitter) Single Sign-On (SSO)

### Effortless user onboarding in FastAPI app via X (Twitter) Single-Sign-On

![](../assets/1_5ydmDW39jMhR-AU1CAPZPw.webp)

## What SSO stands for?

[Single Sign-On (SSO)](https://aigents.co/learn?search=SSO) is a convenient and secure authentication method that allows users to access multiple applications and services with a single set of login credentials. Instead of remembering and entering separate usernames and passwords for each application, SSO streamlines the process by providing a centralized login system. This not only enhances user experience but also improves security by reducing the risk of password-related vulnerabilities. Various SSO providers have emerged to cater to the increasing demand for streamlined access management.

## Goal

In this article, we will demonstrate a Single Sign-On implementation in FastAPI to login users in a system via **X (Twitter)** **sign-in**.
>  For the equivalent processes with other providers you can follow those links to articles of this series:
>  *1. [*Facebook SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-facebook-single-sign-on-sso-b10865535029)
>  *2. [Microsoft SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-microsoft-single-sign-on-sso-d0a0ab248c36)*
>  *3. [Spotify SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-spotify-single-sign-on-sso-4f461b95344c)*
>  *4*. [Google SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-google-single-sign-on-sso-47454e2e2859)
>  5. [LinkedIn SSO in FastAPI](https://itnext.io/fastapi-linkedin-single-sign-on-sso-b1a0118b02d7)
>  6. [GitLab SSO in FastAPI](https://medium.com/gitconnected/fastapi-gitlab-single-sign-on-sso-624fe442ec56)
>  *7. [GitHub SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-github-single-sign-on-sso-f6b942395649)*

## Implementation
>  All of this article’s pieces of code are included in a dedicated GitHub [repository](https://github.com/chrisK824/fastapi-sso-example) that can be cloned/forked to test out the code or use it for one of your projects!
>  If you find it useful please leave it a star and share with anyone who might be interested!
>  🚀 **Live demo** at [https://fastapi-sso-example.vercel.app/](https://fastapi-sso-example.vercel.app/)

### Application

Our demonstration example will include a simple FastAPI application with just a minimal User Interface written in Jinja templates and Sqlite3 local storage for the users of the system. The user interface will present login methods to the user and a home page, after login, that will present some minimal counters for the users that have signed up in the application for each different provider of authentication.

### FastAPI authentication

In our demonstration we will use FastAPI with basic credentials and cookie authentication. Along with the basic credentials traditional login form, a user will have also the option to sign in with X (Twitter) and other methods.

### FastAPI SSO

FastAPI SSO is an [open-source library](https://github.com/tomasvotava/fastapi-sso) that normalises the SSO process across some of the most popular providers and makes it easy for the developer to integrate easily the sign-in process.

I’m sure more ways must exist out there but I found that repository exposing the functionality simply enough and straight forward.

### X (Twitter) app setup

In order to use the X (Twitter) Single Sign-On mechanism, an app is needed to be created using the Twitter developers’ platform, let’s follow the steps together:

* Navigate to the platform at https://developer.twitter.com/en/apps . Log in if you haven’t already.

* Press the “Create an App” button to start the process.

![Screenshot by author](../assets/1_aGmGA36OdQvN4ts3EXAnvA.webp)

* Create a developer account. You will have to submit a form with a short explanation of your use case. Worry not, no review time, at least not when I did this (03/2024).

* The developer account will create a default project and default app for you. I do not need anything specific so will use just that. Adapt according to your needs.

![Screenshot by author](../assets/1_521kpIGgj6BigVHyJ5OXgg.webp)

* Select your app, mine is the default app under the default project. Press the “Set up” button in the User authentication settings section.

![](../assets/1_lFbVTsPU07Ao0LMrz1lJmw.webp)

* Start with the configuration. Read permissions will suffice for what we need. Web app for our use case.

![Screenshot by author](../assets/1_Myzn3fFxShlc4RmUoJmiKg.webp)

* Give your app a name if, I just left the default, a home page URL (just use the repository URL if there is no page yet) and define a “Callback URI / Redirect URL”. This callback URL is the callback endpoint where the X (Twitter) sign-in mechanism will redirect at, after its own authentication is done, passing along the user’s information. Notice that I’m using a localhost URI here. That’s because, I’ll try all that locally, since I’m not going to deploy that implementation on some host. Once and if your code is deployed on some server, then this URL should be updated to point to the exact IP/Domain and URL path for your callback endpoint.

![Screenshot by author](../assets/1_XY3RHDd7a4XmK_6zkUwk4w.webp)

* Hit save. The setup is complete. An informational page will be displayed which contains the OAuth 2 Client ID and Secret. Note them down as we are going to use them in a bit in our code.

![Screenshot by author](../assets/1_J0-UNkqkIZf8qnjtOd_agA.webp)

### User interface

Our minimal user interface looks like this:

![Screenshot by author](../assets/1_KxIbC_hHiSWhqAjD6yavFw.webp)

Nothing fancy here, just a form where a user can log in and some different methods to sign-in.

The user interface implementation is done via Jinja template. Of course, any frontend framework can be used to separate the frontend implementation but all that are out of scope for this demo.

All we need to know about that user interface, is what happens when we click the X (Twitter) sign-in button which is described by this piece of HTML code:

      <form class="col-lg-3" method="get" action="/v1/xtwitter/login" style="text-align: center;">
          <button class="login-btn" type="submit"><i class="fa-brands fa-x"></i></button>
      </form>

So, upon that button press (submit), the action that will be performed is to issue a GET request at relative path /v1/xtwitter/login*. *Let’s keep that in mind and see what that means for our API endpoints in a bit.

### API endpoints

Our necessary endpoints for this process to work are looking like that:

    from fastapi import APIRouter, Depends, HTTPException, status
    from fastapi.responses import RedirectResponse
    from database_crud import users_db_crud as db_crud
    from schemas import UserSignUp
    from sqlalchemy.orm import Session
    from database import get_db
    from fastapi_sso.sso.twitter import TwitterSSO
    from starlette.requests import Request
    from authentication import create_access_token, SESSION_COOKIE_NAME
    from dotenv import load_dotenv
    from pathlib import Path
    import os
    
    
    directory_path = Path(__file__).parent
    env_file_path = directory_path.parent / '.env'
    
    load_dotenv()
    XTWITTER_CLIENT_ID = os.getenv("XTWITTER_CLIENT_ID")
    XTWITTER_CLIENT_SECRET = os.getenv("XTWITTER_CLIENT_SECRET")
    
    os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'
    
    xtwitter_sso = TwitterSSO(
        XTWITTER_CLIENT_ID,
        XTWITTER_CLIENT_SECRET,
        "http://localhost:9999/v1/xtwitter/callback",
        allow_insecure_http=True
    )
    
    router = APIRouter(prefix="/v1/xtwitter")
    
    
    @router.get("/login", tags=['X(Twitter) SSO'])
    async def xtwitter_login():
        with xtwitter_sso:
            return await xtwitter_sso.get_login_redirect()
    
    
    @router.get("/callback", tags=['X(Twitter) SSO'])
    async def xtwitter_callback(request: Request, db: Session = Depends(get_db)):
        """Process login response from X(Twitter) and return user info"""
    
        try:
            with xtwitter_sso:
                user = await xtwitter_sso.verify_and_process(request)
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

* The environment variables loaded are the X (Twitter) OAuth Client ID and Secret, the ones we received after setting up our X (Twitter) app in the developers’ platform.

* The TwitterSSO class is included in the imported SSO library that we talked a bit earlier. Notice that during instatiation we need to provide our X (Twitter) app credentials there, as well as our redirect URL, same as callback URL declared in our app. Additionally, since we need to test this locally and without any https protocol enabled, we need to declare that and allow insecure http traffic by setting the related argument to True.

* The /v1/xtwitter/loginendpoint is where the whole mechanism is triggered by. Remember that was the route that our X (Twitter) sign-in button was targetting upon in our form. The function executed calls the get_login_redirect method of the xtwitter_sso which triggers the X (Twitter) sign-in flow in our browser. Notice that the form window declares our app name, the one created in X (Twitter) developers’ platform. I didn’t change it to something nicer, so sorry about that 😇!

## Signing-in in via the User Interface

Let’s trigger the log in process using the X (Twitter) button in our User Interface. This will redirect us here:

![Screenshot by author](../assets/1_XcZ3F3LAOt1pEUFtMXj4gQ.webp)

* The sign-in flow goes through the usual user-password authentication and includes any additional security rules like 2FA via phone etc.

* Once the X (Twitter) sign-in process is finished, the app will redirect to our declared redirect URI, hence [http://localhost:9999/v1/xtwitter/callback](http://localhost:9999/v1/google/callback) which takes us back into our local application and the second endpoint in our code.

* All user’s information is received in *user* object in this line

    user = await xtwitter_sso.verify_and_process(request)

**After this point you can do whatever you want with that information for that user.**

* Personally, in this implementation, I chose to store the user’s email in my database as username for my user model and proceed by signing that user in the API. The chosen method here is to create a JWT token and set it as a cookie in the response. That way the user will remain signed-in while in browser and the function will finish its execution by redirecting the user to the home page at root / path where the Jinja template that is rendered recognises the user information received.

![Screenshot by author](../assets/1_ir2mgO3KQr9qriSaT6SY5A.webp)

The username displayed is the X (Twitter) username received from the SSO mechanism and the table presented are just stats from the local database. Notice that X (Twitter) provider has authenticated one user so far.
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
