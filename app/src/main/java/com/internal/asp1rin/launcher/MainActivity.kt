package com.internal.asp1rin.launcher

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        
        // 여기에 나중에 버튼이나 스위치가 담긴 레이아웃을 설정할 예정입니다.
        // setContentView(R.layout.activity_main) 
    }

    // --- C++ 라이브러리 로드 ---
    companion object {
        init {
            // 우리가 CMakeLists.txt에서 정한 이름인 'BypassModule'을 불러옵니다.
            System.loadLibrary("BypassModule")
        }
    }

    // --- C++ 함수(JNI) 선언 ---
    // main.cpp에서 Java_com_internal_asp1rin_launcher_MainActivity_... 로 만든 이름들과 매칭되어야 합니다.
    
    // 무반동/탄퍼짐 토글
    external fun setNoRecoil(enable: Boolean)
    external fun setNoSpread(enable: Boolean)
    
    // 에임봇 설정
    external fun setAimbotState(enable: Boolean)
    external fun setAimbotFov(fov: Float)
    external fun setAimbotSmooth(smooth: Float)

    // --- 버튼 이벤트 예시 (나중에 UI 버튼과 연결) ---
    /*
    fun onNoRecoilClicked(isChecked: Boolean) {
        setNoRecoil(isChecked)
    }
    */
}
