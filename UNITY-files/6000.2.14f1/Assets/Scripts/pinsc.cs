using FirebaseREST;
using System;
using UnityEngine;
using UnityEngine.UI;

public class pincs : MonoBehaviour
{
    public String ekran = "";
    String pay = "";
    String pin = "";
    public int panno = 0;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {   
        if(GameObject.Find(this.gameObject.name + "/gosterge/but/Pinbutton/pinstate")== null)return;
        int myps =Convert.ToInt32(GameObject.Find(this.gameObject.name + "/gosterge/but/Pinbutton/pinstate").GetComponent<Text>().text);
        var colors = GameObject.Find(this.gameObject.name + "/gosterge/but/Pinbutton").GetComponent<Button>().colors;
        if (myps == 1)
        {
            //GameObject.Find(GO.name + "/gosterge/but/Pinbutton").GetComponent<Button>().colors.normalColor=Color.greenYellow;
            colors.normalColor = Color.greenYellow;
            colors.highlightedColor = Color.greenYellow;
            colors.pressedColor = Color.greenYellow;
            colors.selectedColor = Color.greenYellow;
            colors.disabledColor = Color.greenYellow;

            GameObject.Find(this.gameObject.name + "/gosterge/but/Pinbutton").GetComponent<Button>().colors = colors;
            GameObject.Find(this.gameObject.name + "/gosterge/but/Pinbutton/pinstate").GetComponent<Text>().text = myps.ToString();
        }
        else
        {
            colors.normalColor = Color.gray7;
            colors.highlightedColor = Color.gray7;
            colors.pressedColor = Color.gray7;
            colors.selectedColor = Color.gray7;
            colors.disabledColor = Color.gray7;

            GameObject.Find(this.gameObject.name + "/gosterge/but/Pinbutton").GetComponent<Button>().colors = colors;
            GameObject.Find(this.gameObject.name + "/gosterge/but/Pinbutton/pinstate").GetComponent<Text>().text = myps.ToString();
        }
    }

    public void buttonpresed() 
    {

        String mypinstate = GameObject.Find(this.gameObject.name + "/gosterge/but/Pinbutton/pinstate").GetComponent<Text>().text;



        ekran = GameObject.Find("CHZtext").GetComponent<Text>().text;
                    pay = GameObject.Find("payim").GetComponent<Text>().text;
                    pin = GameObject.Find("pinim").GetComponent<Text>().text;


        String mypinname = GameObject.Find(this.gameObject.name + "/pinname").GetComponent<Text>().text;
        Debug.Log("mypinname: " + mypinname);


        String mypinstatenew = "";
        if (mypinstate != null)
        {
            if (Convert.ToInt32(mypinstate) == 1)
            {
                mypinstatenew = "0";
                GameObject.Find(this.gameObject.name + "/gosterge/but/Pinbutton/pinstate").GetComponent<Text>().text = mypinstatenew;
                
            }
            else
            {
                mypinstatenew = "1";
                GameObject.Find(this.gameObject.name + "/gosterge/but/Pinbutton/pinstate").GetComponent<Text>().text = mypinstatenew;
            }
        }

        Debug.Log("mypinstatenew: " + mypinstatenew);
        Debug.Log("mypinstate:" + mypinstate);

        String oldstr = mypinname + ":" + mypinstate + ",";
        String newstr = mypinname + ":" + mypinstatenew + ",";



        if (GameObject.Find("pinim") != null)
        {

            GameObject.Find("pinim").GetComponent<Text>().text = pin.Replace(oldstr, newstr);
            Debug.Log("REPLACE OLDU");

            Programcs psc = GameObject.Find("Program").GetComponent<Programcs>();




            Debug.Log("Psatirsaymax: " + psc.Psatirsaymax);
            for (int psatirsay = 1; psatirsay < psc.Psatirsaymax; psatirsay++)
            {

                if(psc.pinname[psatirsay] == GameObject.Find(this.gameObject.name + "/pinname").GetComponent<Text>().text) 
                {
                    psc.PinState[psatirsay] = mypinstatenew;
                    psc.ePinState[psatirsay] = mypinstatenew;
                    Debug.Log("pastirsay=" + psatirsay);
                    Debug.Log("PIN STATE GUNCELLENDI: " + psc.PinState[psatirsay]);
                    break;
                }
            }                    


        }


        String yol = GameObject.Find("yoltexttek").GetComponent<Text>().text;
        String giden = GameObject.Find("pinim").GetComponent<Text>().text;

        DatabaseReference saveRefbt = FirebaseDatabase.Instance.GetReference(yol+"/pins/"+ekran+"pin");
        saveRefbt.SetValueAsync(giden, 20, null);


        giden = "9";
        DatabaseReference saveRefsayacbt = FirebaseDatabase.Instance.GetReference(yol + "/r/" + ekran);
        saveRefsayacbt.SetValueAsync(giden, 20, null);


        //int saynt =Convert.ToInt32(GameObject.Find("chzpan" + panno + "/say").GetComponent<Text>().text);


        //if (saynt>8) saynt = 0;
        //else saynt += 1;

        //saveRef = FirebaseDatabase.Instance.GetReference(yol + "/" + ekran + "say");
        //saveRef.SetValueAsync(saynt, 20, null);


    }

    public void sliderchg()
    {
        GameObject.Find(this.gameObject.name + "/gosterge/Slider/value").GetComponent<Text>().text = GameObject.Find(this.gameObject.name + "/gosterge/Slider").GetComponent<Slider>().value.ToString();
    }

    public void sliderpointerDown()
    {
        GameObject.Find(this.gameObject.name + "/gosterge/Slider/value").transform.localScale= new Vector3(1f, 1f, 1f);
    }

    public void sliderpointerUp()
    {
        GameObject.Find(this.gameObject.name + "/gosterge/Slider/value").transform.localScale = new Vector3(0f, 1f, 1f);


        ekran = GameObject.Find("CHZtext").GetComponent<Text>().text;
                    pay = GameObject.Find("payim").GetComponent<Text>().text;
                    pin = GameObject.Find("pinim").GetComponent<Text>().text;


        String mypinname = GameObject.Find(this.gameObject.name + "/pinname").GetComponent<Text>().text;
        Debug.Log("mypinname: " + mypinname);


        String mypinstate = GameObject.Find(this.gameObject.name + "/gosterge/Slider/pinstate").GetComponent<Text>().text;
        String mypinstatenew = GameObject.Find(this.gameObject.name + "/gosterge/Slider/value").GetComponent<Text>().text;


        String pinismi = GameObject.Find(this.gameObject.name + "/pinname").GetComponent<Text>().text;

        String pindegertmp= pin.Substring(pin.IndexOf(pinismi + ":") + pinismi.Length + 1 , pin.Length-(pin.IndexOf(pinismi + ":") + pinismi.Length + 1));
        pindegertmp= pindegertmp.Substring(0, pindegertmp.IndexOf(","));

        String oldstr = mypinname + ":" + pindegertmp + ",";
        String newstr = mypinname + ":" + mypinstatenew + ",";

        

        if (GameObject.Find("pinim") != null)
        { Debug.Log ("oldstr: " + oldstr);
            Debug.Log("oldstr: " + GameObject.Find("pinim").GetComponent<Text>().text);
            GameObject.Find("pinim").GetComponent<Text>().text = pin.Replace(oldstr, newstr);
            Debug.Log("REPLACE OLDU");
            Debug.Log("newstr: " + newstr);
            Debug.Log("newstr: " + GameObject.Find("pinim").GetComponent<Text>().text);
            Programcs psc = GameObject.Find("Program").GetComponent<Programcs>();


            for (int psatirsay = 1; psatirsay < psc.Psatirsaymax; psatirsay++)
            {

                if (psc.pinname[psatirsay] == GameObject.Find(this.gameObject.name + "/pinname").GetComponent<Text>().text)
                {
                    psc.PinState[psatirsay] = mypinstatenew;
                    psc.ePinState[psatirsay] = mypinstatenew;
                  }
            }


        }

        if (oldstr != newstr)
        {
            String yol = GameObject.Find("yoltexttek").GetComponent<Text>().text;
            String giden = GameObject.Find("pinim").GetComponent<Text>().text;
            Debug.Log("giden: " + giden);
            DatabaseReference saveRefsl = FirebaseDatabase.Instance.GetReference(yol + "/pins/" + ekran + "pin");
            saveRefsl.SetValueAsync(giden, 20, null);

            giden = "9";

            DatabaseReference saveRefsayacsl = FirebaseDatabase.Instance.GetReference(yol + "/r/" + ekran);
            saveRefsayacsl.SetValueAsync(giden, 20, null);


            //int saynt = Convert.ToInt32(GameObject.Find("chzpan" + panno + "/say").GetComponent<Text>().text);

            // if (saynt > 8) saynt = 0;
            //else saynt += 1;

            //saveRef = FirebaseDatabase.Instance.GetReference(yol + "/" + ekran + "say");
            //saveRef.SetValueAsync(saynt, 20, null);
        }
    }



}
