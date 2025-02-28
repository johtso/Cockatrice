#include "featureset.h"

#include <QDebug>
#include <QMap>

FeatureSet::FeatureSet()
{
}

QMap<QString, bool> FeatureSet::getDefaultFeatureList()
{
    initalizeFeatureList(featureList);
    return featureList;
}

void FeatureSet::initalizeFeatureList(QMap<QString, bool> &featureList)
{
    // default features [name], [is required to connect]
    featureList.insert("client_id", false);
    featureList.insert("client_ver", false);
    featureList.insert("feature_set", false);
    featureList.insert("user_ban_history", false);
    featureList.insert("room_chat_history", false);
    featureList.insert("client_warnings", false);
    featureList.insert("mod_log_lookup", false);
    featureList.insert("idle_client", false);
    featureList.insert("forgot_password", false);
    featureList.insert("websocket", false);
    featureList.insert("hashed_password_login", false);
    // These are temp to force users onto a newer client
    featureList.insert("2.7.0_min_version", false);
    featureList.insert("2.8.0_min_version", false);
}

void FeatureSet::enableRequiredFeature(QMap<QString, bool> &featureList, QString featureName)
{
    if (featureList.contains(featureName))
        featureList.insert(featureName, true);
}

void FeatureSet::disableRequiredFeature(QMap<QString, bool> &featureList, QString featureName)
{
    if (featureList.contains(featureName))
        featureList.insert(featureName, false);
}

QMap<QString, bool>
FeatureSet::addFeature(QMap<QString, bool> &featureList, QString featureName, bool isFeatureRequired)
{
    featureList.insert(featureName, isFeatureRequired);
    return featureList;
}

QMap<QString, bool> FeatureSet::identifyMissingFeatures(QMap<QString, bool> suppliedFeatures,
                                                        QMap<QString, bool> requiredFeatures)
{
    QMap<QString, bool> missingList;
    QMap<QString, bool>::iterator i;
    for (i = requiredFeatures.begin(); i != requiredFeatures.end(); ++i) {
        if (!suppliedFeatures.contains(i.key())) {
            missingList.insert(i.key(), i.value());
        }
    }
    return missingList;
}

bool FeatureSet::isRequiredFeaturesMissing(QMap<QString, bool> suppliedFeatures, QMap<QString, bool> requiredFeatures)
{
    QMap<QString, bool>::iterator i;
    for (i = requiredFeatures.begin(); i != requiredFeatures.end(); ++i) {
        if (i.value() && suppliedFeatures.contains(i.key())) {
            return true;
        }
    }
    return false;
}
