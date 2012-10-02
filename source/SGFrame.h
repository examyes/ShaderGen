/************************************************************************
* Author(s):    Inderaj Bains and Joshua Doss                           *
* Last Modified: 10/31/2005                                             *
************************************************************************/
/************************************************************************
*                                                                       *
*               Copyright (C) 2002-2005  3Dlabs Inc. Ltd.               *
*                                                                       *
*                        All rights reserved.                           *
*                                                                       *
* Redistribution and use in source and binary forms, with or without    *
* modification, are permitted provided that the following conditions    *
* are met:                                                              *
*                                                                       *
*     Redistributions of source code must retain the above copyright    *
*     notice, this list of conditions and the following disclaimer.     *
*                                                                       *
*     Redistributions in binary form must reproduce the above           *
*     copyright notice, this list of conditions and the following       *
*     disclaimer in the documentation and/or other materials provided   *
*     with the distribution.                                            *
*                                                                       *
*     Neither the name of 3Dlabs Inc. Ltd. nor the names of its         *
*     contributors may be used to endorse or promote products derived   *
*     from this software without specific prior written permission.     *
*                                                                       *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   *
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     *
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS     *
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE        *
* COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, *
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,  *
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      *
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      *
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT    *
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN     *
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                           *
*                                                                       *
************************************************************************/

#pragma once

#include <QMainWindow>

#include "Vector.h"
#include "SGOglNotebook.h"
#include "SGModels.h"
#include "SGShaderGenerator.h"
#include "SGCanvasWrapper.h"

class SGOglNotebook;
class SGShaderTextWindow;
class SGModels;
class SGCanvas;
class SGFixedGLState;
class SGShaderGenerator;
class SGTextures;

class SGFrame : public QMainWindow
{
    Q_OBJECT
public:
    SGFrame(const QString& title);
    ~SGFrame();

    SGOglNotebook* GetOglNotebook(){ return oglNotebook; }

    SGShaderTextWindow* GetShaderTextWindow(){ return shaderText; }
    SGCanvasWrapper* GetCanvasWrapper(){ return canvas; }
    SGCanvas* GetCanvas() { return canvas->GetCanvas(); }

    SGFixedGLState* GetGLState() { return oglNotebook->GetGLState(); }
    SGTextures* GetTextures() { return oglNotebook->GetTextures(); }

    void DrawModel(SGModels::ModelId model) { models->DrawModel(model); }
    void SetCanvasMode(SGCanvasWrapper::GLMode a);
    void SetStatusText(const QString &text);
    bool isPerspective() const;

    const QString & GetVertexShader() { return shaderGen->BuildVertexShader(); }
    const QString & GetFragmentShader() { return shaderGen->BuildFragmentShader(); }

    static SGFrame *instance;
private slots:
    void modelActionTriggered(QAction *action);
    void viewActionTriggered();
    void help();
    void about();
private:
    void createActions();
    void createMenus();
    void createStatusBar();

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *modelMenu;
    QMenu *helpMenu;

    QAction *exitAct;
    QAction *perspAct;
    QAction *torusAct;
    QAction *sphereAct;
    QAction *trefoilAct;
    QAction *kleinAct;
    QAction *conicAct;
    QAction *planeAct;
    QAction *aboutAct;
    QAction *helpAct;

    SGOglNotebook *oglNotebook;
    SGCanvasWrapper *canvas;
    SGShaderTextWindow* shaderText;
    SGModels *models;
    SGShaderGenerator *shaderGen;
};