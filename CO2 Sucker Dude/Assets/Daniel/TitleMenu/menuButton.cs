using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class menuButton : MonoBehaviour
{
    public void StartBtn()
    {
        SceneManager.LoadSceneAsync("MalinMainSceneCopy");
    }
    public void ExitBtn()
    {
        Application.Quit();
    }
}
