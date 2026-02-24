using UnityEngine;
using UnityEngine.UI;

public class Yolbuttoncs : MonoBehaviour
{
    public string Dbykonstr;
    public void yolbuttonvd()
    {
        Dbykonstr = GameObject.Find("Program").GetComponent<Programcs>().dbykonum.ToString();
    }

}
