/*作为服务器*/
#define IS_SERVER
/*其它*/
#define IS_LOGCHAT

/*作为客户端*/
//#define IS_CUSTOMER

using System;
using System.IO;
using System.Net.Sockets;
using System.Text;
using Unity.VisualScripting;
using UnityEngine;
using System.Threading;
using System.Linq;
using System.Collections.Generic;
using System.Net;
using System.Net.WebSockets;

#if IS_SERVER
public class SocketBehaviour : MonoBehaviour
{
    private static SocketBehaviour _singleton;
    public static SocketBehaviour Singleton
    {
        get
        {
            if (_singleton == null)
            {
                _singleton = FindObjectOfType<SocketBehaviour>();
            }
            return _singleton;
        }
    }
    private const int BUFFER_SIZE = 128;
    public string host = "127.0.0.1";
    public int port = 8899;
    private byte[] buffer;
    private TcpListener listener;
    private List<Socket> connectedClients = new List<Socket>();

    // Use this for initialization
    void Start()
    {
        string pathini = System.Environment.CurrentDirectory + "/config.ini";

        Dictionary<string, Dictionary<string, string>> dicini = FileOperate.ParseIniFile(pathini);
        host = dicini["SERVERS"]["ADDRESS"];
        port = int.Parse(dicini["SERVERS"]["PORT"]);

        Debug.Log("ip: " + host + " port: " + port);

        StartServer();
    }

    private void StartServer()
    {
        try
        {
            IPAddress ipAddress = IPAddress.Parse(host);
            listener = new TcpListener(ipAddress, port);
            listener.Start();
            Debug.Log("Server started, waiting for connections...");

            listener.BeginAcceptSocket(new AsyncCallback(AcceptCallback), listener);
        }
        catch (Exception e)
        {
            Debug.Log(e.Message);
        }
    }

    private void AcceptCallback(IAsyncResult ar)
    {
        TcpListener serverListener = (TcpListener)ar.AsyncState;
        Socket clientSocket = serverListener.EndAcceptSocket(ar);
        if (clientSocket != null)
        {
            connectedClients.Add(clientSocket);
            Debug.Log("Client connected: " + clientSocket.RemoteEndPoint.ToString());
#if IS_LOGCHAT
            SocketBehaviour.Singleton.Send("Hwnd:" + TransparentWindow.hwnd.ToString() + ";");
#endif
            // 开始接收该客户端的数据
            Receive(clientSocket);
        }

        // 继续等待下一个客户端连接
        listener.BeginAcceptSocket(new AsyncCallback(AcceptCallback), listener);
    }

    private void Receive(Socket clientSocket)
    {
        if (!clientSocket.Connected)
            return;

        buffer = new byte[BUFFER_SIZE];

        try
        {
            clientSocket.BeginReceive(buffer, 0, BUFFER_SIZE, SocketFlags.None, new AsyncCallback(Receive_Callback), clientSocket);
        }
        catch (Exception e)
        {
            Debug.Log(e.Message);
        }
    }

    private void Receive_Callback(IAsyncResult ar)
    {
        Socket clientSocket = (Socket)ar.AsyncState;

        if (!clientSocket.Connected)
        {
            return;
        }

        int read = clientSocket.EndReceive(ar);

        if (read > 0)
        {
            // 接收消息
            string receiveString = Encoding.UTF8.GetString(buffer, 0, read);
            Debug.Log("Received from client: " + receiveString);

            Loom.AddList(receiveString);

            // 继续接收该客户端的数据
            Receive(clientSocket);
        }
        else
        {
            // 客户端断开连接
            Debug.Log("Client disconnected: " + clientSocket.RemoteEndPoint.ToString());
            clientSocket.Shutdown(SocketShutdown.Both);
            clientSocket.Close();
            connectedClients.Remove(clientSocket);
        }
    }

    public void Send(string message)
    {

        foreach (Socket item in connectedClients)
        {
            if (!item.Connected)
                break;
            byte[] msg = Encoding.ASCII.GetBytes(message);
            item.Send(msg);
        }

    }

    private void OnDisable()
    {
        foreach (Socket clientSocket in connectedClients)
        {
            if (clientSocket.Connected)
            {
                clientSocket.Shutdown(SocketShutdown.Both);
                clientSocket.Close();
            }
        }

        if (listener != null)
        {
            listener.Stop();
        }
    }
}

#endif
#if IS_CUSTOMER
public class SocketBehaviour : MonoBehaviour
{
    private static SocketBehaviour _singleton;
    public static SocketBehaviour Singleton
    {
        get
        {
            if (_singleton == null)
            {
                _singleton = FindObjectOfType<SocketBehaviour>();
            }
            return _singleton;
        }
    }
    private const int BUFFER_SIZE = 128;
    public string host = "127.0.0.1";
    public int port = 8899;
    private byte[] buffer;
    private Socket socket;
    // Use this for initialization
    void Start()
    {
        string pathini=System.Environment.CurrentDirectory + "\\config.ini";

        Dictionary<string, Dictionary<string, string>> dicini = FileOperate.ParseIniFile(pathini);
        host = dicini["SERVERS"]["ADDRESS"];
        port = int.Parse(dicini["SERVERS"]["PORT"]);

        socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        Connect();
    }

    private void Connect()
    {
        try
        {
            socket.Connect(host, port);
        }
        catch (Exception e)
        {
            print(e.Message);
        }

        if (socket.Connected)
        {
            print("Connected");
            SocketBehaviour.Singleton.Send("Hwnd:" + TransparentWindow.hwnd.ToString() + ";");
            Receive();
        }
        else
        {
            print("Connect fail");
        }
    }

    private void Receive()
    {
        if (!socket.Connected)
            return;

        buffer = new byte[BUFFER_SIZE];

        try
        {
            socket.BeginReceive(buffer, 0, BUFFER_SIZE, SocketFlags.None, new AsyncCallback(Receive_Callback), socket);
        }
        catch (Exception e)
        {
            print(e.Message);
        }
    }

    private void Receive_Callback(IAsyncResult ar)
    {
        if (!socket.Connected)
        {
            return;
        }

        int read = socket.EndReceive(ar);

        if (read > 0)
        {
            //接收消息
            string receiveString = Encoding.UTF8.GetString(buffer);
            Debug.Log("接收到消息：" + receiveString);

            Loom.AddList(receiveString);
            Receive();

        }
    }

    public void Send(string message)
    {
        if (!socket.Connected)
            return;

        byte[] msg = Encoding.ASCII.GetBytes(message);
        socket.Send(msg);
    }

    private void OnDisable()
    {
        if (socket.Connected)
        {
            socket.Shutdown(SocketShutdown.Both);
            socket.Close();
        }
    }
}

#endif
