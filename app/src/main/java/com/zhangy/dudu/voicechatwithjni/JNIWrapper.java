package com.zhangy.dudu.voicechatwithjni;

/**
 * Created by Administrator on 2017/5/18.
 */

public class JNIWrapper {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public static native String stringFromJNI();

}
