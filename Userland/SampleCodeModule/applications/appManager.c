#include <appManager.h>
#include <shell.h>
#include <calculator.h>
#include <systemCalls.h>

static void (*applications[MAX_APPS])() = {runCalculator,runShell};

static void (**currentApp)() = &applications[SHELL];

void startApplication(){
    (*currentApp)();
}

void changeApplication(const t_application app){
    if(app.appID>=0 && app.appID<MAX_APPS){
        sys_changeResources(&app);
        currentApp=&applications[app.appID];
        startApplication();
    }
}
