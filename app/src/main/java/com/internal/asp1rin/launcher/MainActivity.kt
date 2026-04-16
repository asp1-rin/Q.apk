package com.internal.asp1rin.launcher

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.SwitchCompat

class MainActivity : AppCompatActivity() {
    external fun setNoRecoil(en: Boolean)
    external fun setNoSpread(en: Boolean)
    external fun setAimbotState(en: Boolean)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        findViewById<SwitchCompat>(R.id.swNoRecoil).setOnCheckedChangeListener { _, isChecked -> setNoRecoil(isChecked) }
        findViewById<SwitchCompat>(R.id.swNoSpread).setOnCheckedChangeListener { _, isChecked -> setNoSpread(isChecked) }
        findViewById<SwitchCompat>(R.id.swAimbot).setOnCheckedChangeListener { _, isChecked -> setAimbotState(isChecked) }
    }

    companion object {
        init { System.loadLibrary("BypassModule") }
    }
}
