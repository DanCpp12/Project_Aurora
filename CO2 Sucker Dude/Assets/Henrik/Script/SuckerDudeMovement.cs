using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class SuckerDudeMovement : MonoBehaviour
{
    Rigidbody rb;
    Vector3 oldTransform = Vector3.zero;
    private bool walking = false;
    public float moveSpeed = 5f;
    public float rotateSpeed = 5f;
    public Animator animator;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
        oldTransform = transform.position;
    }

    void Update()
    {
        if (transform.position != oldTransform)
        {
            walking = true;
            oldTransform = transform.position;
        }
        else
        {
            walking = false;
        }
        
        animator.SetBool("WalkingBool", walking);
    }
}
