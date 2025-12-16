using UnityEngine;
using UnityEngine.UI;

public class chzpanXnamesc : MonoBehaviour
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }


    public void CHZtextguncelle()
    {
        GameObject.Find("CHZtext").GetComponent<Text>().text = this.gameObject.GetComponent<Text>().text;
        GameObject.Find("Program").GetComponent<Programcs>().ekran = GameObject.Find("CHZtext").GetComponent<Text>().text;
        GameObject.Find("Program").GetComponent<Programcs>().pinek = "/pays/" + this.gameObject.GetComponent<Text>().text +"pay";
        GameObject.Find("Program").GetComponent<Programcs>().listening= false;
        GameObject.Find("Program").GetComponent<Programcs>().queryy();


    }

}
