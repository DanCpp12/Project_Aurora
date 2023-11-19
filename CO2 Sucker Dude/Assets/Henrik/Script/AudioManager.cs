using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;

public class AudioManager : MonoBehaviour
{
    public AudioMixer mixer;

    private bool playMusic;
    private AudioSource music;

    public void MusicOnOff()
    {
        playMusic = !playMusic;
        if (playMusic) music.Play();
        if (!playMusic) music.Stop();
    }

}
