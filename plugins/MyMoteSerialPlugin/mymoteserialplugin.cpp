#include "mymoteserialplugin.h"
#include <QtCore/qplugin.h>

QString MyMoteSerialPlugin::pluginName() {
    return QString("MyMoteSerialPlugin");
}

QByteArray MyMoteSerialPlugin::escapeOutput(const QByteArray &output) {
    int count;
    if((count=output.count('#'))==0) return output;
    else {
        QByteArray escaped = output;
        escaped.replace('#',QByteArray(2,'#'));
        return escaped;
    }
}

BootStrapLoader::bslState MyMoteSerialPlugin::incomingByte(quint8 byte) {
    Q_UNUSED(byte);
    return BootStrapLoader::bsl;
}

BootStrapLoader::bslState MyMoteSerialPlugin::afterSerialConnect() {
    QByteArray string("#U#U:05000615000100.#Q");
    return BootStrapLoader::afterConnect;
}

BootStrapLoader::bslState MyMoteSerialPlugin::beforeSerialDisconnect() {
    return BootStrapLoader::idle;
}

Q_EXPORT_PLUGIN2(mymoteserialplugin, MyMoteSerialPlugin);
