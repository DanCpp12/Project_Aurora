using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;

public class AudioManager : MonoBehaviour
{
    public AudioMixer mixer;

    private bool playMusic;
    private bool muteAudio;
    private AudioSource music;

    public void MusicOnOff()
    {
        playMusic = !playMusic;
        if (playMusic) music.Play();
        if (!playMusic) music.Stop();
    }

    public void MuteUnmute()
    {
        muteAudio = !muteAudio;
        if (muteAudio) mixer.SetFloat("MainVolume", 0f);    // Full audio
        if (!muteAudio) mixer.SetFloat("MainVolume", -80f);    // No audio
    }

}
