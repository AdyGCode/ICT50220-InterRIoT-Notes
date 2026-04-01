

https://itnext.io/fastapi-facebook-single-sign-on-sso-b10865535029


## FastAPI: Facebook Single Sign-On (SSO)

![](./1_3_iQDAQ21McB4D5Pk5JhLg.webp)

Single Sign-On (SSO) is a convenient and secure authentication method that allows users to access multiple applications and services with a single set of login credentials. Instead of remembering and entering separate usernames and passwords for each application, SSO streamlines the process by providing a centralized login system. This not only enhances user experience but also improves security by reducing the risk of password-related vulnerabilities. Various SSO providers have emerged to cater to the increasing demand for streamlined access management.

## Goal

In this article, we will demonstrate a Single Sign-On implementation in FastAPI to login users in a system via **Facebook sign-in**.
>  For the equivalent processes with other providers you can follow those links to articles of this series:
>  *1. [Google SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-google-single-sign-on-sso-47454e2e2859)*
>  *2. [GitHub SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-github-single-sign-on-sso-f6b942395649)*
>  *3. [Spotify SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-spotify-single-sign-on-sso-4f461b95344c)*
>  *4. [Microsoft SSO in FastAPI](https://medium.com/@christos.karvouniaris247/fastapi-microsoft-single-sign-on-sso-d0a0ab248c36)*
>  5. [LinkedIn SSO in FastAPI](https://itnext.io/fastapi-linkedin-single-sign-on-sso-b1a0118b02d7)
>  6. [X (Twitter) SSO in FastAPI](https://medium.com/itnext/fastapi-x-twitter-single-sign-on-sso-5725671ad180)
>  7. [GitLab SSO in FastAPI](https://medium.com/gitconnected/fastapi-gitlab-single-sign-on-sso-624fe442ec56)

## Implementation
>  All of this article’s pieces of code are included in a dedicated GitHub [repository](https://github.com/chrisK824/fastapi-sso-example) that can be cloned/forked to test out the code or use it for one of your projects!
>  If you find it useful please leave it a star and share with anyone who might be interested!
>  🚀 **Live demo** at [https://fastapi-sso-example.vercel.app/](https://fastapi-sso-example.vercel.app/)

### Application

Our demonstration example will include a simple FastAPI application with just a minimal user interface written in Jinja templates and Sqlite3 local storage for the users of the system. The user interface will present login methods to the user and a home page, after login, that will present some minimal counters for the users that have signed up in the application for each different provider of authentication.

### FastAPI authentication

In our demonstration we will use FastAPI with basic credentials and cookie authentication. Along with the basic credentials traditional login form, a user will have also the option to sign in with Facebook and other methods.

### FastAPI SSO

FastAPI SSO is an [open-source library](https://github.com/tomasvotava/fastapi-sso) that normalises the SSO process across some of the most popular providers and makes it easy for the developer to integrate easily the sign-in process.

I’m sure more ways must exist out there but I found that repository exposing the functionality simply enough and straight forward.

### Facebook app setup

In order to use the Facebook Single Sign-On mechanism, an app is needed to be created using the Facebook developers’ platform, let’s follow the steps together:

* Navigate to facebook developers’ apps section at [https://developers.facebook.com/apps/](https://developers.facebook.com/apps/) and press the “create app” button.

* A wizard is going to be started, for starters select the option to “Allow people to log in with their Facebook”.

![](../assets/1_qbiB7TBh6IY-9TgwO0rQFw.webp)

* Next, give a name for your app and press “Create app” on the bottom right corner.

![](../assets/1_95p1ncoIvaiovAOXQNJhzw.webp)

* For the created app locate the tab “Settings” on the left menu and select the “Basic” tab. Make sure to include “localhost” in the Apps domain field. This is just enough for our use case as we are going to use the whole mechanism in our local machine. If your application is hosted on some domain, then this domain should be entered here. Note down also the “App ID” and “App secret” that are present on the top fields of the settings form. We will need them later on in our code configuration.

![](../assets/1_ljEcBQFigXs4cxHbvtcsyg.webp)

* Locate the tab “Use cases” in the left menu, press edit for the “Authentication and account creation” option.

![](../assets/1_xXMdUuSdZffb6ADymmsWeg.webp)

* Add the email use case permission.

![](../assets/1_wwfkUyFaZ4Bo0KLNmwKRtg.webp)

* At this point we are ready to go for testing. If you need this App to be published for production usage, then you need to navigate to “Publish -> Go live” section and request a Review for your application.

![](../assets/1_JKqzBLUmE7x-SGQqr7Soaw.webp)

### User interface

Our minimal user interface looks like this:

![Screenshot by author](../assets/1_Gt4TQBVSxWEVPZLMeFLy5g.webp)

Nothing fancy here, just a form where a user can log in and some different methods to sign-in.

The user interface implementation is done via Jinja template. Of course, any frontend framework can be used to separate the frontend implementation but all that are out of scope for this demo.

All we need to know about that user interface, is what happens when we click the Facebook sign-in button which is described by this piece of HTML code:

      <form class="col-lg-2" method="get" action="/v1/facebook/login" style="text-align: center;">
          <button class="login-btn" type="submit">
              <i class="fa-brands fa-facebook"></i>
          </button>
      </form>

So, upon that button press (submit), the action that will be performed is to issue a GET request at relative path /v1/facebook/login*. *Let’s keep that in mind and see what that means for our API endpoints in a bit.

### API endpoints

Our necessary endpoints for this process to work are looking like that:

    from fastapi import APIRouter, Depends, HTTPException, status
    from fastapi.responses import RedirectResponse
    from database_crud import users_db_crud as db_crud
    from schemas import UserSignUp
    from sqlalchemy.orm import Session
    from database import get_db
    from fastapi_sso.sso.facebook import FacebookSSO
    from starlette.requests import Request
    from authentication import create_access_token, SESSION_COOKIE_NAME
    from dotenv import load_dotenv
    from pathlib import Path
    import os
    
    
    directory_path = Path(__file__).parent
    env_file_path = directory_path.parent / '.env'
    
    load_dotenv()
    FACEBOOK_CLIENT_ID =  os.getenv("FACEBOOK_CLIENT_ID")
    FACEBOOK_CLIENT_SECRET =  os.getenv("FACEBOOK_CLIENT_SECRET")
    
    os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'
    
    facebook_sso = FacebookSSO(
        FACEBOOK_CLIENT_ID,
        FACEBOOK_CLIENT_SECRET, 
        "http://localhost:9999/v1/facebook/callback",
        allow_insecure_http=True
    )
    
    router = APIRouter(prefix="/v1/facebook")
    
    
    @router.get("/login", tags=['Facebook SSO'])
    async def facebook_login():
        return await facebook_sso.get_login_redirect()
    
    
    @router.get("/callback", tags=['Facebook SSO'])
    async def facebook_callback(request: Request, db: Session = Depends(get_db)):
        """Process login response from Facebook and return user info"""
    
        try:
            user = await facebook_sso.verify_and_process(request)
            username = user.email
            user_stored = db_crud.get_user(db, username, user.provider)
            if not user_stored:
                user_to_add = UserSignUp(
                    username=username,
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

* The environment variables loaded are the Facebook Client ID and secret, the ones we received after setting up our Facebook app in Facebook developers’ portal.

* The FacebookSSO class is included in the imported SSO library that we talked a bit earlier. Notice that during instatiation we need to provide our app credentials there, as well as our redirect URI. This is the endpoint where the Facebook sign-in mechanism will redirect to after authentication is finished. Additionally, since we need to test this locally and without any https protocol enabled, we need to declare that and allow insecure http traffic by setting the related argument to True.

* The /v1/facebook/loginendpoint is where the whole mechanism is triggered by. Remember that was the route that our Facebook sign-in button was targetting upon in our form. The function executed calls the get_login_redirect method of the facebook_ssoinstance which triggers the Facebook sign-in flow in our browser.

## Signing-in in via the User Interface

Let’s trigger the log in process using the Facebook button in our User Interface. This will redirect us here:

![Screenshot by author](../assets/1_n23Q1-qVnPzA1h3b5GHFuA.webp)

* The sign-in flow goes through the usual user-password authentication of Facebook and includes any additional security rules like 2FA via phone etc.

![Screenshot by author](../assets/1_nvly1J2XDyEbSX4ZHYdDPQ.webp)

* Once the Facebook sign-in process is finished, the Facebook app will redirect to our declared redirect URI, hence [http://localhost:9999/v1/facebook/callback](http://localhost:9999/v1/google/callback) which takes us back into our local FastAPI application and specifically to the second endpoint in our code.

* All user’s information is received in *user* object in this line

    user = await facebook_sso.verify_and_process(request)

**After this point you can do whatever you want with that information for that user.**

* Personally, in this implementation, I chose to store the user’s email in my database as username for my user model and proceed by signing that user in the API. The chosen method here is to create a JWT token and set it as a cookie in the response. That way the user will remain signed-in while in browser and the function will finish its execution by redirecting the user to the home page at root / path where the Jinja template that is rendered recognises the user information received.

![Screenshot by author](../assets/1_Gt4TQBVSxWEVPZLMeFLy5g.webp)

The username displayed is the email received from the Facebook SSO mechanism and the table presented are just statistics from the local database. Notice that Facebook provider has authenticated one user so far.
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


