




#TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

#
#
PRJNAMETOOT = UE55OSSV2
DEFINES += "UE55OSSV2_API="
DEFINES += "UE55OSSV2_API(...)="
#
DEFINES += "UCLASS()=UE55OSSV2_API"
DEFINES += "UCLASS(...)=UE55OSSV2_API"
#
# this is true during development with unreal-editor...

DEFINES += "WITH_EDITORONLY_DATA=1"

## this project only

##


INCLUDEPATH += ../Intermediate/Build/Win64/UnrealEditor/Inc/$$PRJNAMETOOT/UHT
INCLUDEPATH += $$PRJNAMETOOT/Public $$PRJNAMETOOT/Private
#INCLUDEPATH += ../Plugins/NNEPostProcessing/Source/NNEPostProcessing/Public
# we should follow UE project struct to include files, start from prj.Build.cs folder
#
#  The Thirdparty libs
#
#
#
include(defs.pri)
include(inc.pri)
#
## this project only
# INCLUDEPATH += $$UESRCROOT/Runtime/Renderer/Private
##
#
#

DISTFILES += \
    Ue55OSSv2.Target.cs \
    Ue55OSSv2/Ue55OSSv2.Build.cs \
    Ue55OSSv2Editor.Target.cs

HEADERS += \
    Ue55OSSv2/Ue55OSSv2.h

SOURCES += \
    Ue55OSSv2/Ue55OSSv2.cpp

