package com.internal.asp1rin.launcher

import android.os.Bundle
import android.widget.SeekBar
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.SwitchCompat

class MainActivity : AppCompatActivity() {

    external fun setNoRecoil(enable: Boolean)
    external fun setNoSpread(enable: Boolean)
    external fun setAimbotState(enable: Boolean)
    external fun setAimbotFov(fov: Float)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val swNoRecoil = findViewById<SwitchCompat>(R.id.swNoRecoil)
        val swNoSpread = findViewById<SwitchCompat>(R.id.swNoSpread)
        val swAimbot = findViewById<SwitchCompat>(R.id.swAimbot)
        val sbAimbotFov = findViewById<SeekBar>(R.id.sbAimbotFov)
        val txtFovStatus = findViewById<TextView>(R.id.txtFovStatus)

        swNoRecoil.setOnCheckedChangeListener { _, isChecked -> setNoRecoil(isChecked) }
        swNoSpread.setOnCheckedChangeListener { _, isChecked -> setNoSpread(isChecked) }
        swAimbot.setOnCheckedChangeListener { _, isChecked -> setAimbotState(isChecked) }

        sbAimbotFov.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                val finalFov = if (progress < 1) 1.0f else progress.toFloat()
                setAimbotFov(finalFov)
                txtFovStatus.text = "Aimbot FOV: $finalFov"
            }
            override fun onStartTrackingTouch(seekBar: SeekBar?) {}
            override fun onStopTrackingTouch(seekBar: SeekBar?) {}
        })
    }

    companion object {
        init {
            System.loadLibrary("BypassModule")
        }
    }
