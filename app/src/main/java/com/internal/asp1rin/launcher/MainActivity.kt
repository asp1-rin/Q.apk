package com.internal.asp1rin.launcher

import android.os.Bundle
import android.widget.SeekBar
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.SwitchCompat

class MainActivity : AppCompatActivity() {

    // JNI 함수 선언 (C++과 연결)
    external fun setNoRecoil(enable: Boolean)
    external fun setNoSpread(enable: Boolean)
    external fun setAimbotState(enable: Boolean)
    external fun setAimbotFov(fov: Float)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main) // 레이아웃 연결

        // 1. UI 컴포넌트 초기화
        val swNoRecoil = findViewById<SwitchCompat>(R.id/swNoRecoil)
        val swNoSpread = findViewById<SwitchCompat>(R.id/swNoSpread)
        val swAimbot = findViewById<SwitchCompat>(R.id/swAimbot)
        val sbAimbotFov = findViewById<SeekBar>(R.id/sbAimbotFov)
        val txtFovStatus = findViewById<TextView>(R.id/txtFovStatus)

        // 2. 이벤트 리스너 설정 (UI 조작 시 C++ 함수 호출)

        // 무반동 스위치
        swNoRecoil.setOnCheckedChangeListener { _, isChecked ->
            setNoRecoil(isChecked)
        }

        // 탄퍼짐 제거 스위치
        swNoSpread.setOnCheckedChangeListener { _, isChecked ->
            setNoSpread(isChecked)
        }

        // 에임봇 스위치
        swAimbot.setOnCheckedChangeListener { _, isChecked ->
            setAimbotState(isChecked)
        }

        // 에임봇 FOV 슬라이더 ( SeekBar)
        sbAimbotFov.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                // 슬라이더 값이 바뀔 때마다 C++로 값 전송 (최소값 1 보장)
                val finalFov = if (progress < 1) 1.0f else progress.toFloat()
                setAimbotFov(finalFov)
                txtFovStatus.text = "Aimbot FOV: $finalFov"
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {}
            override fun onStopTrackingTouch(seekBar: SeekBar?) {}
        })
    }

    // 라이브러리 로드
    companion object {
        init {
            System.loadLibrary("BypassModule")
        }
    }
}
