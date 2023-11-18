using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ponits : MonoBehaviour
{
    [SerializeField] private int pointMuliplier = 0;
    [SerializeField] private int points = 0;
    [SerializeField] public score Score;

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Smoke")
        {
            points += pointMuliplier;
            Score.Score = points;
        }
    }
}
