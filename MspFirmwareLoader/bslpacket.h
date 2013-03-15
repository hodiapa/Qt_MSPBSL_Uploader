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

#ifndef BSLPACKET_H
#define BSLPACKET_H

#include <QByteArray>

class BSLCoreMessage;
class BSLPacket {
public:
    enum eSequence { seqIdle,seqAckWait,seqHeaderWait,seqLenghtLWait,
                     seqLenghtHWait,seqReplyWait,seqCrcLWait,seqCrcHWait,seqDone,seqError };

    enum eSeqError { errNoError, errTimeout, errCrcCheck };
public:
    BSLPacket();
    virtual ~BSLPacket();
public:
    eSequence sequence() { return mSequence; }
    void setSequence(eSequence seq) { mSequence=seq; }
    int timeout() const { return mTimeout; }
    bool incomingByte(quint8 incoming);
    bool hasReply() const { return mReply!=NULL && mReply->sequence()==seqDone; }
    const BSLPacket *reply() const { return (const BSLPacket *)mReply; }
    BSLPacket *reply();
    void setExtraData(int e1, int e2, int e3) { mExtraData1=e1; mExtraData2=e2; mExtraData3=e3; }
    int extraData1() const { return mExtraData1; }
    int extraData2() const { return mExtraData2; }
    int extraData3() const { return mExtraData3; }
    eSeqError error() const { return mError; }
    void setError(eSeqError err) { mError=err; }
public:
    virtual const QByteArray assemblePacket();
    virtual void deassemblePacket(const QByteArray &);
private:
    quint16 payloadCrc();
    void crcAddByte(quint8 byte);
    quint16 crcAddByte(quint16 crc16,quint8 byte);
private:
    void clear();
private:
    eSequence mSequence;
    eSeqError mError;
    int mTimeout;
protected:
    QByteArray mPayload;
private:
    quint16 mLength;
    quint16 mCrc16;
private:
    BSLPacket *mReply;
private:
    int mExtraData1;
    int mExtraData2;
    int mExtraData3;
};

#endif // BSLPACKET_H
