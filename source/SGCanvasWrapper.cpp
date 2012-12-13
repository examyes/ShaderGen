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

#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>

#include "SGCanvasWrapper.h"
#include "SGCanvas.h"
#include "SGFrame.h"
#include "SGFixedGLState.h"
#include "UtilityFunctions.h"

SGCanvasWrapper::SGCanvasWrapper(SGFrame *parent)
    :QFrame(parent)
{
    m_parent = parent;
    mode = GLModeChoiceFixed;

    setFocusPolicy(Qt::StrongFocus);

    QVBoxLayout *topSizer = new QVBoxLayout();

    canvas      = new SGCanvas(parent, this);
    canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGroupBox *gb = new QGroupBox(tr("Select GL Mode"), this);
    gb->setLayout(new QHBoxLayout);
    QRadioButton *fixed = new QRadioButton(tr("FIXED FUNCTIONALITY MODE"), gb);
    fixed->setChecked(true);
    QRadioButton *shader = new QRadioButton(tr("EQUIVALENT SHADER MODE "), gb);
    gb->layout()->addWidget(fixed);
    gb->layout()->addWidget(shader);

    glModeChoice = new QButtonGroup(this);
    glModeChoice->addButton(fixed, 0);
    glModeChoice->addButton(shader, 1);
    connect(glModeChoice, SIGNAL(buttonClicked(int)), SLOT(OnRadio(int)));

    topSizer->addWidget(gb);
    topSizer->addWidget(canvas);
    setLayout(topSizer);
}

void SGCanvasWrapper::OnRadio(int id)
{
    SetMode((GLMode)id);
}

SGFixedGLState* SGCanvasWrapper::GetGLState() 
{
    return m_parent->GetGLState();
}

void SGCanvasWrapper::SwitchMode()
{
    if(mode == GLModeChoiceFixed)
    {
        glModeChoice->button(1)->setChecked(true);
        canvas->SwitchToShaderMode();
        mode = GLModeChoiceShader;
    }
    else if(mode == GLModeChoiceShader)
    {
        glModeChoice->button(0)->setChecked(true);
        mode = GLModeChoiceFixed;
    }
    canvas->updateGL();
}

void SGCanvasWrapper::SetMode(GLMode a)
{
    if(mode == a)
    {
        return;
    }
    SwitchMode();
}


