LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := libboost_system-gcc-mt-1_53
LOCAL_SRC_FILES := lib/libboost_system-gcc-mt-1_53.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := libboost_filesystem-gcc-mt-1_53
LOCAL_SRC_FILES := lib/libboost_filesystem-gcc-mt-1_53.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := libtorrent-rasterbar
LOCAL_SRC_FILES := lib/libtorrent-rasterbar.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libwrapper

LOCAL_CFLAGS := -DBOOST_ASIO_HASH_MAP_BUCKETS=1021 \
				-DBOOST_FILESYSTEM_VERSION=3 \
				-DUNICODE \
				-DWITH_SHIPPED_GEOIP_H \
				-DTORRENT_BUILDING_STATIC \
				-DBOOST_ASIO_SEPARATE_COMPILATION \
				-DBOOST_ASIO_ENABLE_CANCELIO \
				-DTORRENT_USE_ICONV=0 \
				-DTORRENT_USE_TOMMATH 

LOCAL_C_INCLUDES := /Users/chublix/libtorrent-android/jni/include \
					$(LOCAL_PATH)

LOCAL_SRC_FILES := 	wrapper.cpp

LOCAL_LDLIBS := -llog
					
LOCAL_STATIC_LIBRARIES := libboost_system-gcc-mt-1_53 \
						  libboost_filesystem-gcc-mt-1_53 \
						  libtorrent-rasterbar

include $(BUILD_SHARED_LIBRARY)
