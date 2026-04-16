package com.internal.asp1rin.launcher

import android.os.Bundle
import android.graphics.Color
import android.view.View
import android.widget.*
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    companion object {
        init { System.loadLibrary("admin-logic") }
    }

    private external fun activateSystem()
    private external fun toggleFeature(enabled: Boolean)

    private val admins = listOf("chupx", "kou", "szb", "liar", "pay", "juni")

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val layout = LinearLayout(this).apply {
            orientation = LinearLayout.VERTICAL
            setBackgroundColor(Color.parseColor("#121212"))
            setPadding(50, 100, 50, 50)
            gravity = android.view.Gravity.CENTER
        }

        val input = EditText(this).apply { hint = "ADMIN ID"; setTextColor(Color.WHITE) }
        val btn = Button(this).apply { text = "LOGIN" }
        val switch = Switch(this).apply { 
            text = "ENABLE MOD (RECOIL/AIM)"; setTextColor(Color.CYAN)
            visibility = View.GONE 
        }

        btn.setOnClickListener {
            if (admins.contains(input.text.toString().trim())) {
                activateSystem()
                input.visibility = View.GONE
                btn.visibility = View.GONE
                switch.visibility = View.VISIBLE
                Toast.makeText(this, "ADMIN ACCESS GRANTED", Toast.LENGTH_SHORT).show()
            }
        }

        switch.setOnCheckedChangeListener { _, isChecked -> toggleFeature(isChecked) }

        layout.addView(input); layout.addView(btn); layout.addView(switch)
        setContentView(layout)
    }
}
