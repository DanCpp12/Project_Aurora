using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class smokefx : MonoBehaviour
{
    Camera mainCamera;
    public float timeToFullpuffad;
    public Vector3 targetScale = new Vector3(10f, 10f, 1f); // Den �nskade slutskalan
    private Vector3 initialScale; // Den ursprungliga skalan d�r objektet b�rjar

    void Start()
    {
        mainCamera = Camera.main;
        timeToFullpuffad = Random.Range(4f, 6f);
        initialScale = transform.localScale;
        StartCoroutine(Scale());
    }

    void LateUpdate()
    {
        transform.LookAt(mainCamera.transform);
        transform.Rotate(0, 180, 0);
    }

    IEnumerator Scale()
    {
        float elapsedTime = 0.0f;

        while (elapsedTime < timeToFullpuffad)
        {
            transform.localScale = Vector3.Lerp(initialScale, targetScale, (elapsedTime / timeToFullpuffad));
            elapsedTime += Time.deltaTime;
            yield return null;
        }

        transform.localScale = targetScale; // Se till att slutskalan �r exakt den �nskade skalan vid avslutning
    }
}
