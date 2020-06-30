#ifndef CHANNEL_LIST_MANAGER_H
#define CHANNEL_LIST_MANAGER_H

#include <QFile>
#include <QVector>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QAbstractListModel>

using namespace std;

class list_item
{
public:
    list_item();
    list_item(QString name, QString url);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    QString channel_name;
    QString channel_url;
};

class channel_list_manager : public QAbstractListModel
{
    Q_OBJECT
private:
    void read_config();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
public:
    channel_list_manager(QObject *parent = nullptr);
    void write_config();
    QVector<list_item> channels;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // CHANNEL_LIST_MANAGER_H
