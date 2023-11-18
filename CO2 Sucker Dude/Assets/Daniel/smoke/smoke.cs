using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class smoke : MonoBehaviour
{
    [SerializeField] private List<GameObject> Positions = new List<GameObject>();
    [SerializeField] private GameObject Smoke;
    [SerializeField] private float loopDelay = 0;
    [SerializeField] private float internalDelay = 0;
    [SerializeField] private float subtractInternalDelay = 0;
    private float i = 0;
    private int indexer;

    private void Start()
    {
        InvokeRepeating("spawnSmoke", loopDelay, loopDelay);

    }

    void spawnSmoke()
    {
        indexer = Random.Range(0, Positions.Count);
        if (i == 0)
        {
            Instantiate(Smoke, Positions[indexer].transform.position, Quaternion.identity);
        }
        i++;
        if (i > internalDelay)
        {
            i = 0;
            internalDelay -= subtractInternalDelay;
        }
    }
}
