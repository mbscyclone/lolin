using UnityEngine;

public class scene0sc : MonoBehaviour
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void firebasescenecagir()
    {
                UnityEngine.SceneManagement.SceneManager.LoadScene("firebasescene");
    }

    public void mqttscenecagir()
    {
        UnityEngine.SceneManagement.SceneManager.LoadScene("mqttscene");
    }
}
