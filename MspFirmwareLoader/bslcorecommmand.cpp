/****************************************************************************
** Copyright (c) 2012 Stefano Pagnottelli
** Web: http://github.com/persuader72/Qt_MSPBSL_Uploader
**
** This file is part of Nome-Programma.
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

#include "bslcorecommmand.h"

BSLCoreCommmand::BSLCoreCommmand(quint8 command,quint32 address) : BSLPacket() {
    mCommand=command;
    mAddress=address;
}

const QByteArray BSLCoreCommmand::assemblePacket() {
    if((mAddress&0xFF000000)==0) mPayload.resize(4+mCoreCommmandPayload.size());
    else mPayload.resize(1+mCoreCommmandPayload.size());

    int i=0;
    mPayload[i++]=mCommand;
    if((mAddress&0xFF000000)==0) {
        mPayload[i++]=(quint8)(mAddress&0x0000FF);
        mPayload[i++]=(quint8)((mAddress&0x00FF00)>>8);
        mPayload[i++]=(quint8)((mAddress&0xFF0000)>>16);
    }
    for(int j=0;j<mCoreCommmandPayload.size();j++) mPayload[i++]=mCoreCommmandPayload.at(j);

    return BSLPacket::assemblePacket();
}
