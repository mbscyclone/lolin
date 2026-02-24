using FirebaseREST;
using System;
using UnityEngine;
using UnityEngine.UI;

public class Fbsave : MonoBehaviour
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }


    float diyalogsay1=0;

    // Update is called once per frame
    void Update()
    {
        if (GameObject.Find("errtext").GetComponent<Text>().text != "") 
        {
            diyalogsay1 += Time.fixedDeltaTime;
            GameObject.Find("errtext").transform.localScale= new Vector3(1,1,1);
            if(diyalogsay1 > 10) { GameObject.Find("errtext").GetComponent<Text>().text = "";diyalogsay1 = 0;}
        }
        else
        {
            GameObject.Find("errtext").transform.localScale = new Vector3(0, 0, 0);
        }

        
    }

    public void fbsave()
    {
        int err = 0;
        GameObject Firebasesettingsobj = GameObject.Find("FirebaseSettingsObj");

        GameObject InputURLobj = GameObject.Find("dbkayit-url-InputField");
        GameObject InputAPI_KEYobj = GameObject.Find("dbkayit-apikey-InputField");

        if (InputURLobj.GetComponent<InputField>().text.IndexOf("rtdb.firebaseio.com")>0)
        {

            if (InputAPI_KEYobj.GetComponent<InputField>().text.Length > 20)
            {
                int dbn = Convert.ToInt32(GameObject.Find("dbno-InputField").GetComponent<InputField>().text);
                if (dbn > 5 || dbn < 0) err = 3;
                else
                {
                    PlayerPrefs.SetString("FBURL", InputURLobj.GetComponent<InputField>().text);
                    PlayerPrefs.SetString("FBAPI", InputAPI_KEYobj.GetComponent<InputField>().text);
                    PlayerPrefs.SetString("dburl" + GameObject.Find("dbno-InputField").GetComponent<InputField>().text, InputURLobj.GetComponent<InputField>().text);
                    PlayerPrefs.SetString("dbapi" + GameObject.Find("dbno-InputField").GetComponent<InputField>().text, InputAPI_KEYobj.GetComponent<InputField>().text);

                    GameObject.Find("Panelalt/db" + dbn.ToString()).GetComponent<Text>().text = PlayerPrefs.GetString("dburl"+ GameObject.Find("dbno-InputField").GetComponent<InputField>().text);
                    GameObject.Find("Panelust/db" + dbn.ToString()).GetComponent<Text>().text = PlayerPrefs.GetString("dburl"+ GameObject.Find("dbno-InputField").GetComponent<InputField>().text);
                    GameObject.Find("dbpaneller").transform.position = new Vector3(GameObject.Find("dbpaneller").transform.position.x, (dbn*60)-60, 200);
                    GameObject.Find("Secilidbtext").GetComponent<Text>().text = PlayerPrefs.GetString("dburl" + GameObject.Find("dbno-InputField").GetComponent<InputField>().text);
                    GameObject.Find("Secilidbapikeytext").GetComponent<Text>().text = PlayerPrefs.GetString("dbapi" + GameObject.Find("dbno-InputField").GetComponent<InputField>().text);
                    GameObject.Find("Program").GetComponent<Programcs>().dbykonum = dbn;

                }
            }
            else { err = 2; }
        }
        else { err = 1; }


        if (err != 0)
        {
            if (err == 1) { GameObject.Find("errtext").GetComponent<Text>().text = "DATABASE URL ? "; }
            if (err == 2) { GameObject.Find("errtext").GetComponent<Text>().text = "API KEY ? "; }
            if (err == 3) { GameObject.Find("errtext").GetComponent<Text>().text = "SERVER NO ? "; }
        }

        if (err == 0)
        {
            Firebasesettingsobj.GetComponent<FirebaseSettings>().DATABASE_URL = PlayerPrefs.GetString("FBURL");
            Firebasesettingsobj.GetComponent<FirebaseSettings>().WEB_API = PlayerPrefs.GetString("FBAPI");
        }
    }

    public void Dbgetir() 
    {
        int err = 0;
        int dbn = Convert.ToInt32(GameObject.Find("dbno-InputField").GetComponent<InputField>().text);
        if (dbn > 5 || dbn < 0) err = 3;
        else
        {
            if (PlayerPrefs.GetString("dburl" + GameObject.Find("dbno-InputField").GetComponent<InputField>().text).Length < 10)
            { err = 4; }
            else
            {
                GameObject InputURLobj = GameObject.Find("dbkayit-url-InputField");
                GameObject InputAPI_KEYobj = GameObject.Find("dbkayit-apikey-InputField");
                InputURLobj.GetComponent<InputField>().text = PlayerPrefs.GetString("dburl" + GameObject.Find("dbno-InputField").GetComponent<InputField>().text);
                InputAPI_KEYobj.GetComponent<InputField>().text = PlayerPrefs.GetString("dbapi" + GameObject.Find("dbno-InputField").GetComponent<InputField>().text);
            }
        }
        if (err == 3) { GameObject.Find("errtext").GetComponent<Text>().text = "SERVER NO ? "; }
        if (err == 3) { GameObject.Find("errtext").GetComponent<Text>().text = GameObject.Find("dbno-InputField").GetComponent<InputField>().text + " TE DB KAYDI YOK "; }
    }

}
