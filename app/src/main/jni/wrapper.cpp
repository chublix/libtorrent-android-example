#include <android/log.h>
#include <string>
#include <iostream>
#include <boost/system/error_code.hpp>
#include "wrapper.h"

JNIFUNC(jstring, MainActivity, stringFromJNI)
{
    std::string tag("GREETING");
    std::string message("Hello from C++!");
    __android_log_print(ANDROID_LOG_INFO, tag.c_str(), "%s", message.c_str());
    std::string jniMessage("Hello from JNI!, Bleat!!!!");
    return env->NewStringUTF(jniMessage.c_str());
}

void printError(std::string errMessage) {
    __android_log_print(ANDROID_LOG_ERROR, "Libtorrent", "%s", errMessage.c_str());
}

TorrentWrapper::TorrentWrapper() {
    m_session = new session();
    boost::system::error_code ec;
    m_session->listen_on(std::make_pair(6881, 6885), ec);
    if (ec) {
        printError(ec.message());
    }
}

TorrentWrapper::~TorrentWrapper() { }

void TorrentWrapper::addNewTorrentFromFile(const string& torrentFilePath, const string& savePath) {
    add_torrent_params params;
    params.save_path = savePath;
    boost::system::error_code ec;
    params.ti = new libtorrent::torrent_info(torrentFilePath, ec);
    if (ec) {
        printError(ec.message());
        return;
    }
    libtorrent::torrent_handle handle = m_session->add_torrent(params, ec);
    if (ec) {
        printError(ec.message());
        return;
    }
}

void TorrentWrapper::addNewTorrentFromMagnetURI(const string& magnetURI, const string& savePath) {
    add_torrent_params params;
    params.save_path = savePath;
    params.url = magnetURI;
    boost::system::error_code ec;
    m_session->add_torrent(params, ec);
    if (ec) {
        printError(ec.message());
        return;
    }
}

vector<torrent_handle> TorrentWrapper::getTorrentsList() const {
    return m_session->get_torrents();
}

// JAVA Wrapper


JNIEXPORT void JNICALL
Java_com_example_chublix_torrenttest_MainActivity_initTorrent(JNIEnv *env, jclass type) {
    TorrentWrapper::getInstance();
}

JNIEXPORT void JNICALL
Java_com_example_chublix_torrenttest_MainActivity_addNewTorrentFromFile(JNIEnv *env, jclass type,
                                                                        jstring torrentFilePath_,
                                                                        jstring savePath_) {
    const char *torrentFilePath = env->GetStringUTFChars(torrentFilePath_, 0);
    const char *savePath = env->GetStringUTFChars(savePath_, 0);

    TorrentWrapper::getInstance().addNewTorrentFromFile(string(torrentFilePath), string(savePath));

    env->ReleaseStringUTFChars(torrentFilePath_, torrentFilePath);
    env->ReleaseStringUTFChars(savePath_, savePath);
}

JNIEXPORT void JNICALL
Java_com_example_chublix_torrenttest_MainActivity_addNewTorrentFromMagnetURI(JNIEnv *env,
                                                                             jclass type,
                                                                             jstring magnetURI_,
                                                                             jstring savePath_) {
    const char *magnetURI = env->GetStringUTFChars(magnetURI_, 0);
    const char *savePath = env->GetStringUTFChars(savePath_, 0);

    TorrentWrapper::getInstance().addNewTorrentFromMagnetURI(string(magnetURI), string(savePath));

    env->ReleaseStringUTFChars(magnetURI_, magnetURI);
    env->ReleaseStringUTFChars(savePath_, savePath);
}

JNIEXPORT jobject JNICALL
Java_com_example_chublix_torrenttest_MainActivity_getTorrentsList(JNIEnv *env, jclass type) {

    jclass cls = env->FindClass("com/example/chublix/torrenttest/TorrentItem");
    jmethodID constructor = env->GetMethodID(cls, "<init>", "()V");

    jfieldID nameFieldID = env->GetFieldID(cls, "name", "Ljava/lang/String;");
    jfieldID savePathFieldID = env->GetFieldID(cls, "savePath", "Ljava/lang/String;");
    jfieldID downloadSpeedFieldID = env->GetFieldID(cls, "downloadSpeed", "I");
    jfieldID uploadSpeedFieldID = env->GetFieldID(cls, "uploadSpeed", "I");
    jfieldID peersCountFieldID = env->GetFieldID(cls, "peersCount", "I");
    jfieldID seedsCountFieldID = env->GetFieldID(cls, "seedsCount", "I");
    jfieldID downloadProgressFieldID = env->GetFieldID(cls, "downloadProgress", "F");

    vector<torrent_handle> torrents = TorrentWrapper::getInstance().getTorrentsList();

    jobjectArray array = env->NewObjectArray(torrents.size(), cls, NULL);

    for (int i = 0; i < torrents.size(); i++) {
        torrent_handle handle = torrents[i];
        jobject item = env->NewObject(cls, constructor);

        jstring name = env->NewStringUTF(handle.status().name.c_str());
        jstring savePath = env->NewStringUTF(handle.status().save_path.c_str());

        env->SetObjectField(item, nameFieldID, name);
        env->SetObjectField(item, savePathFieldID, savePath);
        env->SetIntField(item, downloadSpeedFieldID, handle.status().download_rate);
        env->SetIntField(item, uploadSpeedFieldID, handle.status().upload_rate);
        env->SetIntField(item, peersCountFieldID, handle.status().num_peers);
        env->SetIntField(item, seedsCountFieldID, handle.status().num_seeds);
        env->SetFloatField(item, downloadProgressFieldID, handle.status().progress);

        env->SetObjectArrayElement(array, i, item);
    }

    return array;
}
