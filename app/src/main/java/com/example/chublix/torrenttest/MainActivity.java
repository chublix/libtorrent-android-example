package com.example.chublix.torrenttest;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import java.io.File;
import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    static public String APP_TAG = "TorrentTest";

    static {
        System.loadLibrary("wrapper");
    }

    private static native String stringFromJNI();
    private static native void initTorrent();

    private static native void addNewTorrentFromFile(String torrentFilePath, String savePath);
    private static native void addNewTorrentFromMagnetURI(String magnetURI, String savePath);
    private static native TorrentItem[] getTorrentsList();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        File extStore = Environment.getExternalStorageDirectory();
        String path = extStore.toString() + "/Torrent/Files";
        String magnetURI = "magnet:?xt=urn:btih:2c078d8eb74d002b6d2c68f56f9faa62b87b63ca&dn=Maroon+5+-+V++%28Deluxe+Version%29+2014+%5BMP3%40320kbps%5D&tr=udp%3A%2F%2Ftracker.openbittorrent.com%3A80&tr=udp%3A%2F%2Fopen.demonii.com%3A1337&tr=udp%3A%2F%2Ftracker.coppersurfer.tk%3A6969&tr=udp%3A%2F%2Fexodus.desync.com%3A6969";
        initTorrent();
        addNewTorrentFromMagnetURI(magnetURI, path);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public void onButtonClick(View v) {
//        Toast.makeText(getApplicationContext(), stringFromJNI(), 1).show();
        List<TorrentItem> list = Arrays.asList(getTorrentsList());
        if (!list.isEmpty()) {
            TorrentItem item = list.get(0);
            Toast.makeText(getApplicationContext(), item.name, 1).show();
            Log.d(APP_TAG, item.name);
            Log.d(APP_TAG, item.savePath);
            Log.d(APP_TAG, "Progress: " + Float.toString(item.downloadProgress * 100));
        } else {
            Toast.makeText(getApplicationContext(), "List is emty =(", 1).show();
        }
    }
}
