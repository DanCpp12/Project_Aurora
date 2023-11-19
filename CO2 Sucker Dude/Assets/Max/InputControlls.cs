using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;


public class InputControlls : MonoBehaviour
{
        [Header("Components")]
    public Rigidbody rb;
    
    //An empty object transform to tell the code which way the camera is facing and making
    //that the forward transform
    public Transform CameraKompass;
    
    [SerializeField] private GameObject Body;

    [SerializeField] private GameObject gunArm;

    [SerializeField] private GameObject lookAtObject;
    
    
    [Header("Controls")]
    public PlayerInput controls;
    private InputAction move;
    private InputAction interact;
    
    [Header("Camera controls")]
    public GameObject playerCamera;
    
    
    [Header("Movement")]
    private Vector2 movementInput;
    private Vector3 moveDirection;
    
    public float speed = 5f;
    public float rotationSpeed = 10f;
    
    private void Awake()
    {
        //Assigns Player input and gives orientation a starting Value
        controls = new PlayerInput();
    }



    private void OnEnable()
    {
        move = controls.Player.Movement; 
        
        move.Enable();
        move.performed += OnMove;

    }
    
    private void OnDisable()
    {
        move.performed -= OnMove;
        move.Disable();
    }
    
    private void OnMove(InputAction.CallbackContext obj)
    {
        movementInput = obj.ReadValue<Vector2>();

    }
    
    private void SetDirection()
    {
        //Shortening variable
        var cpos = playerCamera.transform.position;
        
        //Subtracts the cameras position from the position you're looking at to get 
        var newViewDirection = lookAtObject.gameObject.transform.position - new Vector3(cpos.x, lookAtObject.gameObject.transform.position.y, cpos.z);
        CameraKompass.forward = newViewDirection.normalized;
        
        //Combines player input to the current forward direction
        moveDirection = CameraKompass.forward * movementInput.y + CameraKompass.right * movementInput.x;
        
        //Two different variables so that only the arm turns up and down while turning, not the entire body
        
        //The body
        Body.transform.right = playerCamera.transform.right;
            
        //The arm
        gunArm.transform.forward = playerCamera.transform.forward;
    }
    
    private void SetVelocity()
    {
        //Movement
        transform.Translate(moveDirection * speed  * Time.deltaTime);

        
    }
    private void Update()
    {
        SetDirection();
        SetVelocity();
    }
}
