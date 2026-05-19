// Copyright Valii Studio 2026. All Rights Reserved.

#include "MetaAttributionSubsystem.h"
#include "MetaAttributionSettings.h"
#include "MetaAttributionBridge.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#endif

void UMetaAttributionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogMetaAttribution, Log, TEXT("MetaAttributionSubsystem Initialized"));

    // Automatically initialize the Facebook SDK when the game starts
    InitializeFacebookSDK();
}

// 1. Initialize for CPI Tracking (Call on Game Startup)
void UMetaAttributionSubsystem::InitializeFacebookSDK()
{
    UE_LOG(LogMetaAttribution, Log, TEXT("Initializing Facebook SDK..."));
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jclass FMSDKClass = FAndroidApplication::FindJavaClass("com/facebook/appevents/AppEventsLogger");
        if (FMSDKClass != nullptr)
        {
            jmethodID ActivateMethod = Env->GetStaticMethodID(FMSDKClass, "activateApp", "(Landroid/app/Application;)V");
            if (ActivateMethod != nullptr)
            {
                jobject GameActivity = FAndroidApplication::GetGameActivityThis();
                jclass ActivityClass = Env->GetObjectClass(GameActivity);
                jmethodID GetApplicationMethod = Env->GetMethodID(ActivityClass, "getApplication", "()Landroid/app/Application;");
                
                if (GetApplicationMethod != nullptr)
                {
                    jobject ApplicationObj = Env->CallObjectMethod(GameActivity, GetApplicationMethod);
                    Env->CallStaticVoidMethod(FMSDKClass, ActivateMethod, ApplicationObj);
                    UE_LOG(LogMetaAttribution, Log, TEXT("Facebook SDK activateApp called successfully."));
                    Env->DeleteLocalRef(ApplicationObj);
                }
                else
                {
                    UE_LOG(LogMetaAttribution, Error, TEXT("Failed to find getApplication method."));
                }
                
                Env->DeleteLocalRef(ActivityClass);
            }
            else
            {
                UE_LOG(LogMetaAttribution, Error, TEXT("Failed to find activateApp method for Facebook SDK."));
            }
        }
    }
#else
    UE_LOG(LogMetaAttribution, Warning, TEXT("Facebook SDK initialization skipped (Platform is not Android)."));
#endif
}

// 2. Custom Event Logging for AEO (TutorialComplete, MatchStarted)
void UMetaAttributionSubsystem::LogFacebookEvent(FString EventName)
{
    UE_LOG(LogMetaAttribution, Log, TEXT("Attempting to log Facebook Event: %s"), *EventName);
#if PLATFORM_ANDROID
    if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
    {
        jclass FMSDKClass = FAndroidApplication::FindJavaClass("com/facebook/appevents/AppEventsLogger");
        if (FMSDKClass != nullptr)
        {
            // Get Logger instance
            jmethodID NewLoggerMethod = Env->GetStaticMethodID(FMSDKClass, "newLogger", "(Landroid/content/Context;)Lcom/facebook/appevents/AppEventsLogger;");
            if (NewLoggerMethod != nullptr)
            {
                jobject LoggerObject = Env->CallStaticObjectMethod(FMSDKClass, NewLoggerMethod, FAndroidApplication::GetGameActivityThis());

                if (LoggerObject != nullptr)
                {
                    // Call logEvent
                    jmethodID LogEventMethod = Env->GetMethodID(FMSDKClass, "logEvent", "(Ljava/lang/String;)V");
                    if (LogEventMethod != nullptr)
                    {
                        jstring JEventName = Env->NewStringUTF(TCHAR_TO_UTF8(*EventName));
                        Env->CallVoidMethod(LoggerObject, LogEventMethod, JEventName);
                        Env->DeleteLocalRef(JEventName);
                        UE_LOG(LogMetaAttribution, Log, TEXT("Successfully logged Facebook Event: %s"), *EventName);
                    }
                    else
                    {
                        UE_LOG(LogMetaAttribution, Error, TEXT("Failed to find logEvent method for Facebook Event: %s"), *EventName);
                    }
                    Env->DeleteLocalRef(LoggerObject);
                }
            }
        }
    }
#else
    UE_LOG(LogMetaAttribution, Warning, TEXT("Facebook Event logging skipped (Platform is not Android): %s"), *EventName);
#endif
}
