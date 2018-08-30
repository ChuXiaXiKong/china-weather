/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    lixiang@kylinos.cn/kobe24_lixiang@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WEATHERWORKER_H
#define WEATHERWORKER_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkConfigurationManager>
#include <QHostInfo>

#include "data.h"

class WeatherWorker : public QObject
{
    Q_OBJECT

public:

    enum WeatherType
    {
        Type_Observe,
        Type_Forecast
    };

    explicit WeatherWorker(QObject *parent = 0);
    ~WeatherWorker();


    bool isNetWorkSettingsGood();
    void netWorkOnlineOrNot();

    void refreshObserveWeatherData(const QString &cityId);
    void refreshForecastWeatherData(const QString &cityId);

    void requestPingBackWeatherServer();
    void requestPostHostInfoToWeatherServer(QString hostInfo);

    void AccessDedirectUrl(const QString &redirectUrl, WeatherType weatherType);
    void AccessDedirectUrlWithPost(const QString &redirectUrl);

    QString getErrorCodeDescription(QString errorCode);

signals:
    void observeDataRefreshed(const ObserveWeather &data);
    void forecastDataRefreshed(const QList<ForecastWeather> &datas);
    void nofityNetworkStatus(bool status);

public slots:
    void onWeatherObserveReply();
    void onWeatherForecastReply();
    void onPingBackPostReply();
    void networkLookedUp(const QHostInfo &host);

private:
    QNetworkAccessManager *m_networkManager = nullptr;
    QString m_hostInfoParameters;
};

#endif // WEATHERWORKER_H