#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>
#include <QString>
#include <QVector>
#include <QFile>
#include <QDir>

typedef struct program{
    QString id;
    int sss;
    QString exepath;
    QString dispname;
}program;

typedef struct page{
    int index;
    QString pagename;
    QVector<program> veccontents;
}page;

class jsonioctrl
{
public:
    QString _default_editor_path;
    QVector<page> _vecpages;
public:
    static jsonioctrl& instance()
    {
        static jsonioctrl _instance;
        return _instance;
    }
    bool readconfig(QString configfile)
    {
        this->_default_editor_path="/root";
        this->_vecpages.clear();
        QFile file(configfile);
        QByteArray bytearray;
        if(!file.open(QIODevice::ReadOnly))
            bytearray = _default;
        else
            bytearray = file.readAll();
        QJsonDocument jsondoc = QJsonDocument::fromJson(bytearray);
        this->_default_editor_path = jsondoc.object().value("editor").toString();
        QJsonArray jsonarray = jsondoc.object().value("pages").toArray();
        int arrsize = jsonarray.size();
        for(int i = 0;i<arrsize;i++){
            QJsonObject subobject = jsonarray.at(i).toObject();
            page temppage;
            QString pagename = subobject.value("pagename").toVariant().toString();
            int index = subobject.value("index").toVariant().toInt();
            temppage.pagename = pagename;
            temppage.index = index;
            temppage.veccontents.clear();
            QJsonArray programarray = subobject["contents"].toArray();
            int programcount = programarray.size();
            for(int j = 0;j<programcount;j++)
            {
                int programsss = programarray.at(j).toObject().value("sss").toVariant().toInt();
                QString programexec = programarray.at(j).toObject().value("program").toVariant().toString();
                QString programid = programarray.at(j).toObject().value("id").toVariant().toString();
                QString programname = programarray.at(j).toObject().value("name").toVariant().toString();
                program tempprogram;
                tempprogram.id = programid;
                tempprogram.sss = programsss;
                tempprogram.exepath = programexec;
                tempprogram.dispname = programname;
                temppage.veccontents.push_back(tempprogram);
            }
            _vecpages.push_back(temppage);
        }
        file.close();
        return true;
    }
    void parse(QVector<page> vecpages,QJsonArray& arr)
    {
        for(auto it = vecpages.begin(); it != vecpages.end(); ++it)
        {
            QJsonObject page;
            page["pagename"] = it->pagename;
            page["index"] = it->index;
            QJsonArray contents;
            for(auto itt = it->veccontents.begin(); itt != it->veccontents.end(); ++itt)
            {
                QJsonObject program1;
                program1["id"] = itt->id;
                program1["sss"] = itt->sss;
                program1["program"] = itt->exepath;
                program1["name"] = itt->dispname;
                contents.push_back(program1);
            }
            page["contents"] = contents;
            arr.push_back(page);
        }
    }
    bool writeconfig(QString configfile)
    {
        QFile file(configfile);
        if(!file.open(QIODevice::WriteOnly))
            return false;
        QJsonObject jsonobj;
        QJsonArray pages;
        parse(_vecpages,pages);
        jsonobj["pages"] = pages;
        jsonobj["editor"] = QJsonValue(this->_default_editor_path);
        QJsonDocument jsondoc(jsonobj);
        QByteArray bytearray = jsondoc.toJson();
        file.write(bytearray);
        file.close();
        return true;
    }
private:
    jsonioctrl() = default;
    ~jsonioctrl() = default;
    QByteArray _default = "{\n    \"pages\": [\n        {\n            \"contents\": [\n                {\n                    \"id\": \"12342344\",\n                    \"name\": \"FileExchange\",\n                    \"program\": \"/FileExchange/build-FileExchange-Desktop_Qt_5_9_0_GCC_64bit-Release/FileExchange\",\n                    \"sss\": 0\n                },\n                {\n                    \"id\": \"53462332\",\n                    \"name\": \"TransWorker-DNC\",\n                    \"program\": \"/home/kylin/215/build-TransWorker-DNC-Desktop_Qt_5_9_0_GCC_64bit-Debug/TransWorker-DNC\",\n                    \"sss\": 1\n                },\n                {\n                    \"id\": \"45678548\",\n                    \"name\": \"prjuntitledxx\",\n                    \"program\": \"/home/kylin/prjuntitled/bin/a.sh\",\n                    \"sss\": 1\n                }\n            ],\n            \"index\": 1,\n            \"pagename\": \"aaa\"\n        },\n        {\n            \"contents\": [\n                {\n                    \"id\": \"2462364\",\n                    \"name\": \"ptm-1055_xx\",\n                    \"program\": \"/ptm-1055/bin/replay.sh\",\n                    \"sss\": 0\n                },\n                {\n                    \"id\": \"756326621\",\n                    \"name\": \"replay.sh\",\n                    \"program\": \"/Replay_protobuf_GCH_2021-11-11/bin/replay.sh\",\n                    \"sss\": 0\n                },\n                {\n                    \"id\": \"65735725\",\n                    \"name\": \"symp\",\n                    \"program\": \"/home/kylin/symp_yx_tsxs/run_release.sh\",\n                    \"sss\": 1\n                }\n            ],\n            \"index\": 2,\n            \"pagename\": \"ccc\"\n        },\n        {\n            \"contents\": [\n                {\n                    \"id\": \"230516193831105\",\n                    \"name\": \"1065test\",\n                    \"program\": \"/home/kylin/SendT0Outer/bin/a.sh\",\n                    \"sss\": 1\n                }\n            ],\n            \"index\": 3,\n            \"pagename\": \"ddd\"\n        }\n    ]\n}\n";
};
