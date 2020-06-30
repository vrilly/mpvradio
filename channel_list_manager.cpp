#include "channel_list_manager.h"

list_item::list_item()
{
}

list_item::list_item(QString name, QString url)
{
    this->channel_name = name;
    this->channel_url = url;
}

void list_item::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        this->channel_name = json["name"].toString();
    if (json.contains("url") && json["url"].isString())
        this->channel_url = json["url"].toString();
}

void list_item::write(QJsonObject &json) const
{
    json["name"] = this->channel_name;
    json["url"] = this->channel_url;
}

void channel_list_manager::read(const QJsonObject &json)
{
    if (json.contains("channels") && json["channels"].isArray())
    {
        QJsonArray array = json["channels"].toArray();
        this->channels.reserve(array.size());
        for (int i = 0; i < array.size(); ++i)
        {
            QJsonObject listObject = array[i].toObject();
            list_item listItem;
            listItem.read(listObject);
            this->channels.append(listItem);
        }
    }
}

void channel_list_manager::write(QJsonObject &json) const
{
    QJsonArray array;
    for (const list_item &item : this->channels)
    {
        QJsonObject listObject;
        item.write(listObject);
        array.append(listObject);
    }
    json["channels"] = array;
}

void channel_list_manager::read_config()
{
    QString configFilePath;
    configFilePath =
        QStandardPaths::locate(QStandardPaths::ConfigLocation, "mpvradio.json");
    if (configFilePath.size() == 0)
        return ;
    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::ReadOnly))
    {
        qWarning("Cannot open config file %s",
                 configFilePath.toStdString().c_str());
        return ;
    }
    QByteArray channelListData = configFile.readAll();
    QJsonDocument channelListJson(QJsonDocument::fromJson(channelListData));
    read(channelListJson.object());
}

void channel_list_manager::write_config()
{
    QString configFilePath;
    configFilePath =
        QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) +
        "/mpvradio.json";
    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::WriteOnly))
    {
        qWarning("Cannot open config file %s",
                 configFilePath.toStdString().c_str());
        return ;
    }
    QJsonObject channelListJson;
    write(channelListJson);
    configFile.write(QJsonDocument(channelListJson).toJson());
    endResetModel();
}

channel_list_manager::channel_list_manager(QObject *parent)
{
    (void)parent;
    read_config();
}

int channel_list_manager::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return (this->channels.size());
}

QVariant channel_list_manager::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    switch (role)
    {
    case Qt::DisplayRole:
        return (this->channels.at(row).channel_name);
        break;
    }
    return (QVariant());
}
