/****************************************************************************
** Copyright (c) 2012 Stefano Pagnottelli
** Web: http://github.com/persuader72/Qt_MSPBSL_Uploader
**
** This file is part of Qt_MSPBSL_Uploader.
**
** Nome-Programma is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Nome-Programma is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Nome-Programma.  If not, see <http://www.gnu.org/licenses/>.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qextserialport.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include "bslsendpacketevent.h"
#include "bslrxpassword.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow) {
    ui->setupUi(this);
    mBsl = new BootStrapLoader(this);
    connect(mBsl,SIGNAL(onStateChanged(int)),this,SLOT(onBslStateChanged(int)));
    connect(mBsl,SIGNAL(onErrorRised(QString,QString)),SLOT(onBslErrorRised(QString,QString)));
    startTimer(333);
}

MainWindow::~MainWindow() {
    mBsl->quit();
    mBsl->wait();
    delete mBsl;
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *) {
}

void MainWindow::onBslStateChanged(int state) {
}

void MainWindow::onBslErrorRised(const QString &title, const QString &text) {
    QMessageBox::warning(this,title,text);
}

void MainWindow::on_FirmwareLoadButton_clicked() {
    QString fn=QFileDialog::getOpenFileName(this,"Select intel hex firmware file","","*.hex");
    if(!fn.isNull()) {
        QFile f(fn);
        ui->FirmwareSelectedFile->setText(fn);
        if(!f.open(QIODevice::ReadOnly)) {
            qDebug()<< f.errorString();
        } else {
            parser.parseFile(f);
        }
    }

    BSLCoreCommmand *pktVersion = new BSLCoreCommmand(0x19,BSLCORE_NULL_ADDRESS);
    QApplication::instance()->postEvent (mBsl, new BslSendPacketEvent(pktVersion));
}

void MainWindow::on_SerialConnectButton_clicked() {
    if(mBsl->isRunning()) {
        QMessageBox::warning(this,"Open Serial Port error","Serial port is already opened!");
    } else {
        mBsl->setPortName(ui->SerialPortNameEdit->text());
        mBsl->start();
    }
}
