using FirebaseREST;
using MiniJSON;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Net.NetworkInformation;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.InputSystem.LowLevel;
using UnityEngine.Rendering;
using UnityEngine.UI;


public class Programcs : MonoBehaviour
{

    public String ekran = "";
    public String[] chzname;
    public String epay = "";
    public String esay = "";


    public String[] pinsatir = new String[10];
    public String[] pinname = new String[10];
    public String[] pinmode = new String[10];
    public String[] pinsignaltype = new String[10];
    public String[] pinminvalue = new String[10];
    public String[] PinState = new String[10];
    public String[] ePinState = new String[10];
    public String[] pinmaxvalue = new String[10];
    public String[] pinlabel = new String[10];


    public String asd = "";
    public String yol = "";
    public bool valuechg = false;

    public float testsayisi = 0;

    public int ilksatirYkonumu = -140;  //UI deki ilk pin objesinin satýr koordinatý = 0;
    public int Yartis = 170;         //Sonraki satir icin ekleme
    public int SuandakiYkonum = -140;   //Þu andaki satir kordinatý Y
    public int Psatirsaymax = 10;

    public String pinek = "";
    public float querysayac = 0f;
    bool rquery = false;
    public bool listening = false;
    private void Start()
    {

     chzname = new String[6];

     pinsatir = new String[10];
     pinname = new String[10];
     pinmode = new String[10];
     pinsignaltype = new String[10];
     pinminvalue = new String[10];
     PinState = new String[10];
     ePinState = new String[10];
     pinmaxvalue = new String[10];
     pinlabel = new String[10];



    Dbleriyerlestir();
    }

    String oldasd = "";
    private void Update()
    {
        if (valuechg == true)
        {
            Debug.Log("asd: " + asd);
            ekran = GameObject.Find("CHZtext").GetComponent<Text>().text;

            if (ekran.Length < 1)
            {
                pinek = "/r";
            }

            if (ekran.Length > 0 && pinek.IndexOf(ekran + "pay") > -1)
            {
                payoku();
                pinek = "/" + ekran + "pin";
            }

            if (ekran.Length > 0 && pinek.IndexOf(ekran + "pin") > -1)
            {
                pinoku();
                pinek = "/" + ekran + "pin";
                if(listening==true) tekgorunumguncelle();
            }

            valuechg = false;
        }


        if (asd != null)
         if (asd.Length > 0)
         {
            if (asd != oldasd)
            {
                    oldasd = asd;
                    if (pinek=="/r") rguncelle();
                else 
                    if (pinek == "/pays/" + ekran + "pay") 
                    {
                      payoku();
                        queryy();
                    }
                    else
                    if (pinek == "/pins/" + ekran + "pin")
                    {
                        if(querysayac>2f)
                        {
                            querysayac = 0f;
                            if (listening == false) fblisten();
                        }
                        else
                        {
                            querysayac += Time.fixedDeltaTime;
                        }
                        pinoku();
                    }


                }

                if (pinek == "/pins/" + ekran + "pin")
                {
                    if (querysayac > 2f)
                    {
                        querysayac = 0f;
                        if(listening==false) fblisten();
                    }
                    else
                    {
                        querysayac += Time.fixedDeltaTime;
                    }
                    pinoku();
                }


            }
         if(rquery==false)queryy();
    }

    public void Dbleriyerlestir()
    {
        if (PlayerPrefs.GetString("dburl1") == "" || PlayerPrefs.GetString("dburl1") == null)
        {
            GameObject.Find("Main Camera").transform.position = GameObject.Find("K0").transform.position;
            GameObject.Find("dbno-InputField").GetComponent<InputField>().text = "1";
            return;
        }
        else
        {
            GameObject.Find("Main Camera").transform.position = GameObject.Find("K2").transform.position;

            FirebaseSettings firebaseSettingscs = GameObject.Find("FirebaseSettingsObj").GetComponent<FirebaseSettings>();
            //PlayerPrefs.SetString("FBURL",firebaseSettingscs.DATABASE_URL);
            //PlayerPrefs.SetString("FBAPI", firebaseSettingscs.WEB_API);
            firebaseSettingscs.DATABASE_URL = PlayerPrefs.GetString("FBURL");
            firebaseSettingscs.WEB_API = PlayerPrefs.GetString("FBAPI");
            if (firebaseSettingscs.DATABASE_URL != "" && firebaseSettingscs.DATABASE_URL != null)
            {
                GameObject.Find("Secilidbtext").GetComponent<Text>().text = firebaseSettingscs.DATABASE_URL;
                GameObject.Find("Secilidbapikeytext").GetComponent<Text>().text = firebaseSettingscs.WEB_API;
            }
        }

        for (int i = 1; i < 6; i++)
        {
            if (PlayerPrefs.GetString("dburl" + i.ToString()) != "" && PlayerPrefs.GetString("dburl" + i.ToString()) != null)
            {
                GameObject.Find("Panelust/db" + i.ToString()).GetComponent<Text>().text = PlayerPrefs.GetString("dburl" + i.ToString());
            } else break;
        }


    }

    public void fblisten()
    {
        listening = true;
        GameObject Firebasesettingsobj = GameObject.Find("FirebaseSettingsObj");
        DatabaseReference dbref = FirebaseDatabase.Instance.GetReference(yol + "/pins/" + ekran + "pin");
        dbref.ValueChanged += (sender, a) =>
        {
            asd = a.Snapshot.GetRawJsonValue();
            valuechg = true;
        };
        Debug.Log("LISTENING BAÞLADI");
    }

    public void Geridonanasayfa()
    {
        GameObject.Find("Main Camera").transform.position = GameObject.Find("K2").transform.position;
    }

    public void geridontotalgorunum()
    {
        oldasd = " ";asd = "";
        GameObject.Find("Main Camera").transform.position = GameObject.Find("K6").transform.position;
    }

    public void geridonyolbelirle()
    {
        GameObject.Find("Main Camera").transform.position = GameObject.Find("K4").transform.position;
        ekran = "";
        GameObject.Find("CHZtext").GetComponent<Text>().text=ekran;
    }

    public void yolbelirle()
    {
         GameObject.Find("Main Camera").transform.position = GameObject.Find("K4").transform.position;




        String Dbykonstr = dbykonum.ToString();
        for (int i = 1; i < 7; i++)
        {
            GameObject.Find("yol-plane/" + i.ToString() + "/text").GetComponent<InputField>().text = PlayerPrefs.GetString("yol" + Dbykonstr + "-" + i.ToString());
        }

    }



    public void queryy()
    { 
        yol = GameObject.Find("yoltext").GetComponent<Text>().text;
        if(pinek=="")return;
        Debug.Log("yol: " + yol + pinek);
        Query query = FirebaseDatabase.Instance.GetReference(yol + pinek);
        query = query.OrderByKey();
        query.GetValueAsync(10, (res) =>
        {
            if (res.success)
            {
                asd = res.data.GetRawJsonValue();
                GameObject Rawdatatext = GameObject.Find("Rawdata");
                Rawdatatext.GetComponent<Text>().text = asd;
                //if (ekran.Length > 0) tekgorunumguncelle();
                //else if(pinek=="/r")rguncelle();
                rquery = true;
                //Debug.Log(asd);
            }
            else
            {
                //Debug.Log(res.message);
            }
        });

        valuechg = false;

        //if(GameObject.Find("Panelcon").transform.position.x==-6000) 

    }


    public void rguncelle() {
        String rtmp = asd;
        if (asd.Length < 2) return;
        rtmp = rtmp.Substring(rtmp.IndexOf("{\"") + 2, rtmp.Length - (rtmp.IndexOf("{\"") + 2));
        for (int i=1;i<4;i++)
        {
            Debug.Log("rtmp baþ: " + rtmp);
            chzname[i] = rtmp.Substring(0, rtmp.IndexOf("\""));
            GameObject.Find("chzpan" + i.ToString() + "/name").GetComponent<Text>().text = chzname[i];

            if(rtmp.IndexOf("\",")>-1)
                rtmp = rtmp.Substring(rtmp.IndexOf("\",") + 3, rtmp.Length - (rtmp.IndexOf("\",") + 3)); // cihazismi ve ",  sildik
            else
            {

                rtmp = "";
                break;
            }

        }

        //Debug.Log("rtmp: " + rtmp);


        /*
        for(int i = 1; i < 3; i++)
        {
            //chztmp=chztmp.Substring(1,chztmp.Length-1);
            if (rtmp.Length > 0)
            {
                chzname[i] = rtmp.Substring(1, rtmp.IndexOf("pay\":\"") - 1);
                rtmp = rtmp.Substring(chzname[i].Length + 6, rtmp.Length - (chzname[i].Length + 6));
                GameObject.Find("chzpan" + i.ToString() + "/name").GetComponent<Text>().text = chzname[i];
                Debug.Log("chzname[" + i.ToString() + "]: " + chzname[i]);
            }
        }
        */



    }



    /*
    public void queryy2()
    {

        Query query = FirebaseDatabase.Instance.GetReference(yol+pinek);
        query = query.OrderByKey();
        query.GetValueAsync(10, (res) =>
        {
            if (res.success)
            {
                asd = res.data.GetRawJsonValue();
                GameObject Rawdatatext = GameObject.Find("Rawdata");
                Rawdatatext.GetComponent<Text>().text = asd;
                Debug.Log(asd);
                totalgorunumguncelle();
            }
            else
            {
                Debug.Log(res.message);
            }
        });
        
        valuechg = false;

        //if(GameObject.Find("Panelcon").transform.position.x==-6000) 

    }
    */

    
    public void Datagostersayfasi()
    {
        if(GameObject.Find("CHZtext").GetComponent<Text>().text.Length>0) ekran = GameObject.Find("CHZtext").GetComponent<Text>().text=""; ;
        yol = GameObject.Find("yol-plane/" + gameObject.transform.parent.name + "/text").GetComponent<InputField>().text;
         if (GameObject.Find("yol-plane/" + dbykonum.ToString() + "/text").GetComponent<InputField>().text.Length > 0)
        {
            // data göster sayfasýna git ve dinlemeye baþla

            Debug.Log(GameObject.Find("yol-plane/" + gameObject.transform.parent.name + "/text").GetComponent<InputField>().text);
            yol = GameObject.Find("yol-plane/" + gameObject.transform.parent.name + "/text").GetComponent<InputField>().text;
            GameObject.Find("Main Camera").transform.position = GameObject.Find("K6").transform.position;

            String Dbykonstr = dbykonum.ToString();
            PlayerPrefs.SetString("yol" + Dbykonstr + "-" + gameObject.transform.parent.name, GameObject.Find("yol-plane/" + gameObject.transform.parent.name + "/text").GetComponent<InputField>().text);

            String url = PlayerPrefs.GetString("FBURL");
            GameObject.Find("urlonektext").GetComponent<Text>().text = url.Substring(8, url.IndexOf("-default") - 8);
            GameObject.Find("yoltext").GetComponent<Text>().text = yol;
            GameObject.Find("urlonektexttek").GetComponent<Text>().text = url.Substring(8, url.IndexOf("-default") - 8);
            GameObject.Find("yoltexttek").GetComponent<Text>().text = yol;
            // listen baþla+ //////////////////////////////////////
            GameObject Firebasesettingsobj = GameObject.Find("FirebaseSettingsObj");

            DatabaseReference dbref = FirebaseDatabase.Instance.GetReference(yol +"/r");
            dbref.ValueChanged += (sender, a) =>
            {



                asd = a.Snapshot.GetRawJsonValue();
                valuechg = true;

            };

            /*
             Query query = FirebaseDatabase.Instance.GetReference(queryPathIF.text);


                            if (orderByDropDown.value > 0)
                {
                    switch (orderByDropDown.value)
                    {
                        case 1:
                            query = query.OrderByKey();
                            break;
                        case 2:
                            query = query.OrderByValue();
                            break;
                        case 3:
                            if (!string.IsNullOrEmpty(orderByIF.text))
                            {
                                query = query.OrderByChild(orderByIF.text);
                            }
                            break;
                    }
                }
                if (!string.IsNullOrEmpty(startAtIF.text))
                {
                    query = query.StartAt(startAtIF.text);
                }
                if (!string.IsNullOrEmpty(endAtIF.text))
                {
                    query = query.EndAt(endAtIF.text);
                }
                if (!string.IsNullOrEmpty(equalToIF.text))
                {
                    query = query.EqualTo(equalToIF.text);
                }
                int limitToFirst;
                if (int.TryParse(limitToFirstIF.text, out limitToFirst))
                {
                    query = query.LimitToFirst(limitToFirst);
                }
                int limitToLast;
                if (int.TryParse(limitToLastIF.text, out limitToLast))
                {
                    query = query.LimitToLast(limitToLast);
                }
                query.GetValueAsync(10, (res) =>
                {
                    if (res.success)
                    {
                        resultText.text = res.data.GetRawJsonValue();
                    }
                    else
                    {
                        resultText.text = res.message;
                    }
                });
                break;
        }

             
             
             
             
             
             
             */
            ////////////////////////////////////////// Listen baþla-

        }
    }
    

    public void payoku()
    {
        String paytmp = "";
        String kesilecekolan = "\"";
        paytmp = asd.Substring(asd.IndexOf(kesilecekolan)+kesilecekolan.Length , asd.Length-(asd.IndexOf(kesilecekolan) + kesilecekolan.Length+1));
        Debug.Log("paytmp: " + paytmp);
            GameObject.Find("payim").GetComponent<Text>().text = paytmp;
        pinek = "/pins/" + ekran + "pin"; queryy();
    }

    public void pinoku()
    {
        String pintmp = asd;
        Debug.Log("pintmp baþý: " + pintmp);
        Debug.Log("asd baþý: " + asd);

                pintmp = pintmp.Substring(1, pintmp.Length - 2);
                Debug.Log("pintmp: " + pintmp);
                GameObject.Find("pinim").GetComponent<Text>().text = pintmp;
    }

    public void totalgorunumguncelle()
    {
        String paystmp = "";
        if(asd.IndexOf("\"pays\":")>-1)
        {
            paystmp = asd.Substring(asd.IndexOf("\"pays\":{") + 8, asd.Length - (asd.IndexOf("\"pays\":{")+8));
            paystmp = paystmp.Substring(0, paystmp.IndexOf("},\"pins\":"));
        }
        String pinstmp = "";
        if (asd.IndexOf("\"pins\":") > -1)
        {
            pinstmp = asd.Substring(asd.IndexOf("\"pins\":{") + 8 , asd.Length - (asd.IndexOf("\"pins\":{") + 8));
            pinstmp = pinstmp.Substring(0, pinstmp.IndexOf("\"}")+1);
        }
        else {pinstmp = asd.Substring(1,asd.Length-2);
        }
        //Debug.Log("pays: " + paystmp);
        //Debug.Log("pins: " + pinstmp);
        //Debug.Log("pinstmp baþlangýç: " + pinstmp);

        GameObject.Find("CHZlertext").GetComponent<Text>().text = "";

            for (int i = 1; i < 4; i++)
            {
                //chztmp=chztmp.Substring(1,chztmp.Length-1);
                if (paystmp.Length > 0 || pinstmp.Length>0)
                {


                    // cihaz name esphostname
                    //Debug.Log("paystmp baþ: " + paystmp);
                    //Debug.Log("i: " + i.ToString());

                    if (paystmp.IndexOf("pay\":\"") > -1)
                    {
                        chzname[i] = paystmp.Substring(1, paystmp.IndexOf("pay\":\"")-1);
                        paystmp = paystmp.Substring(chzname[i].Length + 6, paystmp.Length - (chzname[i].Length + 6));
                        GameObject.Find("chzpan" + i.ToString() + "/name").GetComponent<Text>().text = chzname[i];
                        Debug.Log("chzname[" + i.ToString() + "]: " + chzname[i]);
                    }

                if (paystmp.Length > 0)
                {
                    // pay al
                    //Debug.Log("paybaþý ne: " + paystmp);
                    String paytmp = paystmp;

                    paytmp = paytmp.Substring(1, paytmp.Length - 1);
                    paytmp = paytmp.Substring(0, paytmp.IndexOf("\""));
                    //Debug.Log("paytmp: " + paytmp);
                    GameObject.Find("chzpan" + i.ToString() + "/pay").GetComponent<Text>().text = paytmp;
                    paystmp = paystmp.Substring(paytmp.Length + 1, paystmp.Length - (paytmp.Length + 1));
                    //Debug.Log("paystmp devam: " + paystmp);
                }

                        if (pinstmp.IndexOf("pin\":\"") > -1)
                        {
                            pinstmp = pinstmp.Substring(chzname[i].Length + 6, pinstmp.Length - (chzname[i].Length + 6));
                        }
                        // pay al
                        //Debug.Log("pinbaþý ne: " + pinstmp);
                        String pintmp = pinstmp;

                        pintmp = pintmp.Substring(1, pintmp.Length - 1);
                pintmp = pintmp.Substring(0, pintmp.IndexOf("\""));
                        //Debug.Log("pintmp: " + pintmp);
                        GameObject.Find("chzpan" + i.ToString() + "/pin").GetComponent<Text>().text = pintmp;
                        pinstmp = pinstmp.Substring(pintmp.Length + 1, pinstmp.Length - (pintmp.Length + 1));
                        //Debug.Log("pinstmp devam: " + pinstmp);






                if (paystmp.IndexOf("},")>-1 && paystmp.IndexOf("},") < 3)
                    {
                        paystmp = "";
                        break;
                    }
                    if(paystmp.Length<3)
                    {
                    break;
                    }

                /*
                        // pay pinayar
                        if (asd.IndexOf(chzname[i] + "pay\":\"") > -1)
                        {
                            String paytmp = asd;
                            int paybas = paytmp.IndexOf(chzname[i] + "pay\":\"") + chzname[i].Length + 6;
                            paytmp = paytmp.Substring(paybas, paytmp.Length - (paytmp.IndexOf(chzname[i] + "pay\":\"") + chzname[i].Length + 6));
                            //Debug.Log(paytmp);
                            int payson = paytmp.IndexOf("^\"");
                            GameObject.Find("chzpan" + i.ToString() + "/pay").GetComponent<Text>().text = paytmp.Substring(0, payson);
                        }
                */
            }
                        /*
                        // pin pinstate
                        if (pintmp.IndexOf(chzname[i] + "pin\":\"") > -1)
                        {

                            int pinbas = pintmp.IndexOf(chzname[i] + "pin\":\"") + chzname[i].Length+6;

                            pintmp = pintmp.Substring(pinbas, pintmp.IndexOf("\"}") - pinbas);
                            Debug.Log(pintmp);
                            GameObject.Find("chzpan" + i.ToString() + "/pin").GetComponent<Text>().text = pintmp;
                        }

                        */

            }

                    //Debug.Log(chztmp);
                
            


        ekran = GameObject.Find("CHZtext").GetComponent<Text>().text;
        if (ekran.Length > 0) tekgorunumguncelle();


    }



    public void tekgorunumguncelle()
    {
        GameObject.Find("Main Camera").transform.position = GameObject.Find("K8").transform.position;
        Pinsatirlariniolustur();
        Pinsatirlariniguncelle();
    }



    public void Pinsatirlariniolustur()
    {
        String pay = "";
        String pin = "";
        String say = "";

        /*
        ekran = GameObject.Find("CHZtext").GetComponent<Text>().text;
        for (int chzpaneldeara = 1; chzpaneldeara < 12; chzpaneldeara++)
        {
            if (GameObject.Find("chzpan" + chzpaneldeara + "/name") != null)
            {
                if (GameObject.Find("chzpan" + chzpaneldeara + "/name").GetComponent<Text>().text == ekran)
                {
                    pay = GameObject.Find("chzpan" + chzpaneldeara + "/pay").GetComponent<Text>().text;
                    pin = GameObject.Find("chzpan" + chzpaneldeara + "/pin").GetComponent<Text>().text;
                    say = GameObject.Find("chzpan" + chzpaneldeara + "/say").GetComponent<Text>().text;
                }
            }
        }
        */
        pay = GameObject.Find("payim").GetComponent<Text>().text;
        pin = GameObject.Find("pinim").GetComponent<Text>().text;


        if (epay != pay)
        {
            for (int psatirsay = 1; psatirsay < 11; psatirsay++)
            {
                if (GameObject.Find("pin-" + psatirsay.ToString()) != null) DestroyImmediate(GameObject.Find("pin-" + psatirsay.ToString()));
            }
        }



        // pay parçalama için döngü
        String ptm = pay;
        String hum = "";
        String temp = "";

            Debug.Log("ptm BAÞLANGIÇ: " + ptm);

        for (int psatirsay = 1; psatirsay < 11; psatirsay++)
        {

            if (ptm.Length > 2 && ptm.IndexOf("]") > -1 && ptm.IndexOf("|") > -1)
            {
                pinname[psatirsay] = ptm.Substring(1, ptm.IndexOf("|") - 1);
                //Debug.Log("pinname: " + pinname[psatirsay]);

                int xx = ptm.IndexOf("|");
                ptm = ptm.Substring(xx + 1, ptm.Length - (xx + 1));

                pinmode[psatirsay] = ptm.Substring(0, ptm.IndexOf("|"));
                //Debug.Log("pinmode: " + pinmode[psatirsay]);

                xx = ptm.IndexOf("|");
                ptm = ptm.Substring(xx + 1, ptm.Length - (xx + 1));

                pinsignaltype[psatirsay] = ptm.Substring(0, ptm.IndexOf("|"));
                //Debug.Log("pinsignaltype: " + pinsignaltype[psatirsay]);

                xx = ptm.IndexOf("|");
                ptm = ptm.Substring(xx + 1, ptm.Length - (xx + 1));

                pinminvalue[psatirsay] = ptm.Substring(0, ptm.IndexOf("|"));
                //Debug.Log("pinminvalue: " + pinminvalue[psatirsay]);

                xx = ptm.IndexOf("|");
                ptm = ptm.Substring(xx + 1, ptm.Length - (xx + 1));

                ePinState[psatirsay] = ptm.Substring(0, ptm.IndexOf("|"))+".";
                //Debug.Log("ePinState: " + ePinState[psatirsay]);

                xx = ptm.IndexOf("|");
                ptm = ptm.Substring(xx + 1, ptm.Length - (xx + 1));

                pinmaxvalue[psatirsay] = ptm.Substring(0, ptm.IndexOf("|"));
                //Debug.Log("pinmaxvalue: " + pinmaxvalue[psatirsay]);


                xx = ptm.IndexOf("|");
                ptm = ptm.Substring(xx + 1, ptm.Length - (xx + 1));

                pinlabel[psatirsay] = ptm.Substring(0, ptm.IndexOf("]"));
               // Debug.Log("pinlabel: " + pinlabel[psatirsay]);

                xx = ptm.IndexOf("][");
                ptm = ptm.Substring(xx + 1, ptm.Length - (xx + 1));
                Psatirsaymax = psatirsay;
            } else
            {
                Psatirsaymax = psatirsay;
                break;
            }
        }

        // pin parçalama için

            ptm = pin;
         Debug.Log("pin BAÞLANGIÇ : " + ptm);
        for (int psatirsay = 1; psatirsay < Psatirsaymax; psatirsay++)
            {

                if (ptm.Length > 0)
                {

                    //Debug.Log("PinState: " + ptm.Substring(0, ptm.IndexOf(":")));

                    int xx;
                    xx = ptm.IndexOf(":");
                    ptm = ptm.Substring(xx + 1, ptm.Length - (xx + 1));
                if (ptm.Length < 2) break;
                PinState[psatirsay] = ptm.Substring(0, ptm.IndexOf(","));
                Debug.Log("PinState before: " + PinState[psatirsay] + "   pinsignaltype: " + pinsignaltype[psatirsay]);
                if (pinsignaltype[psatirsay].IndexOf("DHT")> -1)
                {
                    if (PinState[psatirsay].IndexOf("t") > -1)
                    {
                        temp = PinState[psatirsay].Substring(PinState[psatirsay].IndexOf("t") + 1, PinState[psatirsay].IndexOf("h") - (PinState[psatirsay].IndexOf("t") + 1));
                        hum = PinState[psatirsay].Substring(PinState[psatirsay].IndexOf("h") + 1, PinState[psatirsay].Length - (PinState[psatirsay].IndexOf("h") + 1));
                        if(hum.Length<2) hum = hum+ "0";
                    }
                }
                else PinState[psatirsay] = (Convert.ToInt32(PinState[psatirsay])).ToString();

                    xx = ptm.IndexOf(",");
                    ptm = ptm.Substring(xx + 1, ptm.Length - (xx + 1));
                }else break;


        }


        GameObject psatirprefab = GameObject.Find("pinsatirlaripanel/pin-");

        SuandakiYkonum = ilksatirYkonumu;
        if(SuandakiYkonum>0) SuandakiYkonum = -147;
        for (int psatirsay = 1; psatirsay < Psatirsaymax; psatirsay++)
        {
            GameObject GO = GameObject.Find("pinsatirlaripanel");
            if (epay != pay)
            {
                GO = Instantiate(psatirprefab, GameObject.Find("pinsatirlaripanel").transform);
                GO.transform.position = new Vector3(GO.transform.position.x, psatirsay * -200, GO.transform.position.z);
                GO.name = "pin-" + psatirsay.ToString();
            }else { GO = GameObject.Find("pin-" + psatirsay.ToString());}

            if (ePinState[psatirsay] != PinState[psatirsay])
            {
                // pin durumu deðiþmiþ


                GameObject.Find(GO.name + "/pinlabel").GetComponent<Text>().text = pinlabel[psatirsay];
                GameObject.Find(GO.name + "/pinname").GetComponent<Text>().text = pinname[psatirsay];
                //GameObject gosterge = GameObject.Find(GO.name + "/gosterge");

                if (pinmode[psatirsay] == "OUT" && pinsignaltype[psatirsay] == "DIG")
                {
                    GameObject.Find(GO.name + "/gosterge/but").transform.localScale = new Vector3(1, 1, 1);
                    GameObject.Find(GO.name + "/gosterge/but/Pinbutton/pinstate").GetComponent<Text>().text = PinState[psatirsay];

                }
                else if (pinmode[psatirsay] == "OUT" && pinsignaltype[psatirsay] == "PWM")
                {
                    GameObject.Find(GO.name + "/gosterge/Slider").transform.localScale = new Vector3(1, 1, 1);
                    GameObject.Find(GO.name + "/gosterge/Slider/pinstate").GetComponent<Text>().text = PinState[psatirsay];
                    GameObject.Find(GO.name + "/gosterge/Slider").GetComponent<Slider>().minValue = Convert.ToInt32(pinminvalue[psatirsay]);
                    GameObject.Find(GO.name + "/gosterge/Slider").GetComponent<Slider>().maxValue = Convert.ToInt32(pinmaxvalue[psatirsay]);
                    GameObject.Find(GO.name + "/gosterge/Slider").GetComponent<Slider>().value = Convert.ToInt32(PinState[psatirsay]);
                    GameObject.Find(GO.name + "/gosterge/Slider/value").GetComponent<Text>().text = PinState[psatirsay];

                    GameObject.Find(GO.name + "/gosterge/Slider/min").GetComponent<Text>().text = pinminvalue[psatirsay];
                    GameObject.Find(GO.name + "/gosterge/Slider/max").GetComponent<Text>().text = pinmaxvalue[psatirsay];


                    GameObject.Find(GO.name + "/gosterge/Slider/value").transform.localScale = new Vector3(0f, 1f, 1f);

                } else if (pinmode[psatirsay] == "INP" && (pinsignaltype[psatirsay] == "ANG" || pinsignaltype[psatirsay] == "DIG") )
                {
                    
                    GameObject.Find(GO.name + "/gosterge/gauge").transform.localScale = new Vector3(1, 1, 1);
                    GameObject.Find(GO.name + "/gosterge/gauge/pinstate").GetComponent<Text>().text = PinState[psatirsay];
                    GameObject.Find(GO.name + "/gosterge/gauge/min").GetComponent<Text>().text = pinminvalue[psatirsay];
                    GameObject.Find(GO.name + "/gosterge/gauge/max").GetComponent<Text>().text = pinmaxvalue[psatirsay];
                    GameObject.Find(GO.name + "/gosterge/gauge/value").GetComponent<Text>().text = PinState[psatirsay];
                    //float angle = (Convert.ToSingle(PinState[psatirsay]) - Convert.ToSingle(pinminvalue[psatirsay])) / (Convert.ToSingle(pinmaxvalue[psatirsay]) - Convert.ToSingle(pinminvalue[psatirsay]));
                    float angle = 135 -Convert.ToInt32( (Convert.ToInt32(PinState[psatirsay])*270)/((Convert.ToInt32(pinmaxvalue[psatirsay])+0.0001f) - Convert.ToInt32(pinminvalue[psatirsay]))) ; 
                    
                    //Debug.Log("angle: " + angle.ToString());
                    GameObject.Find(GO.name + "/gosterge/gauge/sifir/o").transform.rotation = Quaternion.Euler(0, 0, angle);
                }else if (pinmode[psatirsay] == "INP" && pinsignaltype[psatirsay].IndexOf("DHT")>-1)
                {

                    GameObject.Find(GO.name + "/gosterge/dht").transform.localScale = new Vector3(1, 1, 1);
                    GameObject.Find(GO.name + "/gosterge/dht/t").GetComponent<Text>().text = temp;
                    GameObject.Find(GO.name + "/gosterge/dht/h").GetComponent<Text>().text = hum;

                }

                /*
                else if (pinmode[psatirsay] == "INP" && pinsignaltype[psatirsay] == "DIG")
                {
                    GameObject.Find(GO.name + "/gosterge/gostergeled").transform.localScale = new Vector3(1, 1, 1);
                    if (Convert.ToInt32(PinState[psatirsay]) == 1)
                    {
                        GameObject.Find(GO.name + "/gosterge/gostergeled/ledon").transform.localScale = new Vector3(1, 1, 1);
                        GameObject.Find(GO.name + "/gosterge/gostergeled/ledoff").transform.localScale = new Vector3(0, 0, 0);
                    }
                    else
                    {
                        GameObject.Find(GO.name + "/gosterge/gostergeled/ledon").transform.localScale = new Vector3(0, 0, 0);
                        GameObject.Find(GO.name + "/gosterge/gostergeled/ledoff").transform.localScale = new Vector3(1, 1, 1);
                    }
                }
                */

                ePinState[psatirsay] = PinState[psatirsay];
                Debug.Log(ePinState[psatirsay] + " e : p" + PinState[psatirsay]);
            }
            SuandakiYkonum -= Yartis;

        }

        epay = pay;



    }


    public void Pinsatirlariniguncelle()
    {
        ekran = GameObject.Find("CHZtext").GetComponent<Text>().text;
    }


    public void dbkayitsayfasinicagir()
    {
        GameObject.Find("Main Camera").transform.position = GameObject.Find("K0").transform.position;
    }
    public int dbykonum = 1;
    public void dbassagi()
    {
        if(PlayerPrefs.GetString("dburl" + (dbykonum - 1).ToString()).Length > 0)
        {
            dbykonum--;
            GameObject.Find("dbpaneller").transform.position = new Vector3(GameObject.Find("dbpaneller").transform.position.x, (dbykonum * 60)-60, 100);

            GameObject.Find("Secilidbtext").GetComponent<Text>().text = PlayerPrefs.GetString("dburl" + dbykonum.ToString());
            GameObject.Find("Secilidbapikeytext").GetComponent<Text>().text = PlayerPrefs.GetString("dbapi" + dbykonum.ToString());


            FirebaseSettings firebaseSettingscs = GameObject.Find("FirebaseSettingsObj").GetComponent<FirebaseSettings>();
            firebaseSettingscs.DATABASE_URL = GameObject.Find("Secilidbtext").GetComponent<Text>().text;
            firebaseSettingscs.WEB_API = GameObject.Find("Secilidbapikeytext").GetComponent<Text>().text;


            Debug.Log(dbykonum);
        }


    }
    public void dbyukari()
    {
        if (PlayerPrefs.GetString("dburl" + (dbykonum + 1).ToString()).Length > 0)
        {
            dbykonum++;
            GameObject.Find("dbpaneller").transform.position = new Vector3(GameObject.Find("dbpaneller").transform.position.x, (dbykonum * 60) - 60, 100);

            GameObject.Find("Secilidbtext").GetComponent<Text>().text = PlayerPrefs.GetString("dburl" + dbykonum.ToString());
            GameObject.Find("Secilidbapikeytext").GetComponent<Text>().text = PlayerPrefs.GetString("dbapi" + dbykonum.ToString());


            FirebaseSettings firebaseSettingscs = GameObject.Find("FirebaseSettingsObj").GetComponent<FirebaseSettings>();
            firebaseSettingscs.DATABASE_URL = GameObject.Find("Secilidbtext").GetComponent<Text>().text;
            firebaseSettingscs.WEB_API = GameObject.Find("Secilidbapikeytext").GetComponent<Text>().text;


            Debug.Log(dbykonum);
        }

    }

    public int imggoster = 0;
    public void imgchg()
    {

        imggoster += 1;
        if(imggoster>1) imggoster = 0;

        if(imggoster==0)GameObject.Find("CHZfonimg").transform.localScale = new Vector3(0f, 1f, 1f);
        else GameObject.Find("CHZfonimg").transform.localScale = new Vector3(1f, 1f, 1f);

        for (int i = 1; i < 11 ; i++)
        {
            if(GameObject.Find("pin-" + i.ToString() + "/fonimg")==null) break;

            if (imggoster == 0) GameObject.Find("pin-" + i.ToString() + "/fonimg").transform.localScale = new Vector3(0f, 1f, 1f);
            else GameObject.Find("pin-" + i.ToString() + "/fonimg").transform.localScale = new Vector3(1f, 1f, 1f);
        }
    }

}
