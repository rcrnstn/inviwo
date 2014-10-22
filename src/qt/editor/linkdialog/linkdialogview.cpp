/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 * Version 0.6b
 *
 * Copyright (c) 2014 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * Contact: Sathish Kottravel
 *
 *********************************************************************************/

#include <inviwo/qt/editor/linkdialog/linkdialogview.h>
#include <inviwo/qt/editor/linkdialog/linkdialogscene.h>

namespace inviwo {

LinkDialogGraphicsView::LinkDialogGraphicsView(QWidget* parent) : QGraphicsView(parent), scene_(0) {
    setRenderHint(QPainter::Antialiasing, true);
    setMouseTracking(true);
    setDragMode(QGraphicsView::RubberBandDrag);
}

void LinkDialogGraphicsView::setDialogScene(LinkDialogGraphicsScene* scene) {
    QColor bgColor;
    bgColor.setNamedColor("#4d4d4d");
    scene->setBackgroundBrush(bgColor);
    setScene(scene);
    scene_ = scene;
}

void LinkDialogGraphicsView::mouseDoubleClickEvent(QMouseEvent* e) {
    QGraphicsView::mouseDoubleClickEvent(e);
}

LinkDialogGraphicsView::~LinkDialogGraphicsView() {}

} //namespace