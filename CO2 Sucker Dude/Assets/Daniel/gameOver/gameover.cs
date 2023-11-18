using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class gameover : MonoBehaviour
{
    public score score;
    public TextMeshProUGUI soreText;

    void Start()
    {
        soreText.text = "You got " + score.Score.ToString() + " points";
        score.Score = 0;
    }
}
