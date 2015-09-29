#pragma once

#include <jni.h>
#include <libtorrent/session.hpp>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/magnet_uri.hpp>

#ifdef __cplusplus
extern "C" {
#endif

#define JNIFUNC(returnType, activity, function) JNIEXPORT returnType JNICALL Java_com_example_chublix_torrenttest_ ##activity## _ ##function (JNIEnv* env, jclass clazz)

//JNIEXPORT jstring JNICALL Java_com_example_chublix_torrenttest_MainActivity_stringFromJNI(JNIEnv* env, jclass clazz);
JNIFUNC(jstring, MainActivity, stringFromJNI);

JNIEXPORT void JNICALL Java_com_example_chublix_torrenttest_MainActivity_initTorrent(JNIEnv *env, jclass type);

JNIEXPORT void JNICALL Java_com_example_chublix_torrenttest_MainActivity_addNewTorrentFromFile(JNIEnv *env, jclass type, jstring torrentFilePath_, jstring savePath_);

JNIEXPORT void JNICALL Java_com_example_chublix_torrenttest_MainActivity_addNewTorrentFromMagnetURI(JNIEnv *env, jclass type, jstring magnetURI_, jstring savePath_);

JNIEXPORT jobject JNICALL
Java_com_example_chublix_torrenttest_MainActivity_getTorrentsList(JNIEnv *env, jclass type);

#ifdef __cplusplus
}

using namespace libtorrent;
using namespace std;

class TorrentWrapper {
private:
    TorrentWrapper();
    TorrentWrapper( const TorrentWrapper&);
    TorrentWrapper& operator=( TorrentWrapper& );

public:
    static TorrentWrapper& getInstance() {
        static TorrentWrapper  instance;
        return instance;
    }
    ~TorrentWrapper();

public:
    void addNewTorrentFromFile(const string& torrentFilePath, const string& savePath);
    void addNewTorrentFromMagnetURI(const string& magnetURI, const string& savePath);
    vector<torrent_handle> getTorrentsList() const;

private:
    session* m_session;


};

#endif