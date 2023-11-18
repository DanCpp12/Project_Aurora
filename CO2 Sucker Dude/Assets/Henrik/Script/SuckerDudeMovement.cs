using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SuckerDudeMovement : MonoBehaviour
{
    Rigidbody rb;
    public float moveSpeed = 5f;
    public float rotateSpeed = 5f;
    public Animator animator;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    void Update()
    {
        animator.SetFloat("Speed", rb.velocity.magnitude);
    }

    private void FixedUpdate()
    {
        rb.AddForce(transform.forward * moveSpeed * Input.GetAxis("Vertical"), ForceMode.Acceleration);


        // L�s av musens r�relse
        float mouseX = Input.GetAxis("Mouse X");

        // Skapa en rotationsvektor baserat p� musens r�relse
        Vector3 rotation = new Vector3(0f, mouseX, 0f) * rotateSpeed;

        // Applicera rotationen p� karakt�ren
        rb.AddTorque(rotation);
    }
}
