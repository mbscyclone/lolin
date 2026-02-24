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
        if(GameObject.Find("Program").GetComponent<Programcs>().listening == true)
        {
           if(GameObject.Find("Program").GetComponent<Programcs>().dbref!=null) GameObject.Find("Program").GetComponent<Programcs>().dbref.Dispose();
        }
        GameObject.Find("Program").GetComponent<Programcs>().queryy();
        GameObject.Find("Program").GetComponent<Programcs>().listening = false;

    }

}
