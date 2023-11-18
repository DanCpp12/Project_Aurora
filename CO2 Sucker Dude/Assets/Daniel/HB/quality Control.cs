using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class qualityControl : MonoBehaviour
{
    public Slider airQuality;
    private GameObject[] Smoke;

    private void FixedUpdate()
    {
        Smoke = GameObject.FindGameObjectsWithTag("Smoke");
        airQuality.value = Smoke.Length * 0.1f;
    }
}
