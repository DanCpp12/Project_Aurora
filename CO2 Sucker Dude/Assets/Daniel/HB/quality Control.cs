using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class qualityControl : MonoBehaviour
{
    public Slider airQuality;
    private GameObject[] Smoke;

    private void FixedUpdate()
    {
        Smoke = GameObject.FindGameObjectsWithTag("Smoke");
        airQuality.value = Smoke.Length * 0.1f;
        
    }
    public void OnSliderValue()
    {
        if (airQuality.value == 1)
        {
            SceneManager.LoadSceneAsync("gameOverPrototype");
            //Change To Game Over Scene
        }
    }
}
