using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;

public class gameover : MonoBehaviour
{
    public score score;
    public TextMeshProUGUI soreText;

    void Start()
    {
        //score = PlayerPrefs.GetInt("Score", 0);
        soreText.text = "You got " + score.Score.ToString() + " points";
        //score.Score = 0;
    }
    public void RestartBtn()
    {
        //score.Score = 0;
        SceneManager.LoadSceneAsync("MalinMainSceneCopy");
    }
    public void ExitBtn()
    {
        //score.Score = 0;
        SceneManager.LoadSceneAsync("TitleMenu");
    }
}
