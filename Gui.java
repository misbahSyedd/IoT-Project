import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

// we need to Implement action listener to access the buttons on GUI (run commands)
public class Gui extends JFrame implements ActionListener {

	private JTextField userinput1, userinput2, userinput3, userinput4;
	private JLabel display1, display2, display3, display4;
	private JButton button1, button2, button3;
	public Socket mySocket = null;
	public DataOutputStream outStream = null;
	public BufferedReader inStream = null;

	// This is the constructor that build and displays GUI and it invokes the
	// action listeners when we run the buttons on GUI
	public Gui() {

		super("Blink LED(s)"); // Title of GUI
		try {
			mySocket = new Socket("10.0.0.194", 8545); // setting the IP and Port number of Server

			outStream = new DataOutputStream(mySocket.getOutputStream());

			inStream = new BufferedReader(new InputStreamReader(mySocket.getInputStream()));

			setLayout(new FlowLayout());

			display1 = new JLabel("Turn on Pin Number"); // display

			add(display1); // Will add display1 to GUI

			userinput1 = new JTextField(20); // 20 is dimensions of field
			add(userinput1);

			button1 = new JButton("Run");
			button1.setAlignmentX(20);
			add(button1);

			display2 = new JLabel("Turn off Pin Number");

			add(display2);

			userinput2 = new JTextField(20);
			add(userinput2);

			button2 = new JButton("Run");
			add(button2);

			display3 = new JLabel("Blink Pin Number ");

			add(display3);

			userinput3 = new JTextField(5);
			add(userinput3);

			display4 = new JLabel(" For (seconds) ");
			add(display4);

			userinput4 = new JTextField(5);
			add(userinput4);

			button3 = new JButton("Run");
			add(button3);

			button1.addActionListener(this); // invoking the action listeners
			button2.addActionListener(this);
			button3.addActionListener(this);
		} catch (Exception exc) {
			System.out.println("Error is : " + exc.toString());
		}
	}

	@Override
	public void actionPerformed(ActionEvent event) {

		try {

			String input1 = null, input2 = null, input3, input4;
			String turnon = "#turn on pin ", secs = " for ";
			String turnoff = "#turn off pin ";
			String messagetoserver, string = "Command Executed";

			input1 = (userinput1.getText()); // Saving the user input from all 4 input fields

			input2 = (userinput2.getText());

			input3 = (userinput3.getText());

			input4 = (userinput4.getText());

			// If user clicks on button1, this is invoked.
			if (event.getSource() == button1) {

				messagetoserver = turnon + input1;
				outStream.writeBytes(messagetoserver + "\n");
				System.out.println("\n " + messagetoserver + "\n");
				String str = inStream.readLine(); // receive response from server
				System.out.println(str); // print this response
				userinput1.setText("");
				JOptionPane.showMessageDialog(null, string);

			}
			// If user clicks on button2, this is invoked.
			if (event.getSource() == button2) {

				messagetoserver = turnoff + input2;
				outStream.writeBytes(messagetoserver + "\n");
				System.out.println("\n " + messagetoserver + "\n");
				String str = inStream.readLine(); // receive response from server
				System.out.println(str); // print this response
				userinput2.setText("");

			}
			// If user clicks on button3, this is invoked.
			if (event.getSource() == button3) {
				outStream.writeBytes("#Blink Pin " + input3 + " for " + input4 + " sec \n");
				System.out.println("\n #Blink Pin " + input3 + " for " + input4 + " sec \n");
				String str = inStream.readLine(); // receive response from server
				System.out.println(str); // print this response
				userinput3.setText("");
				userinput4.setText("");
			}

		} catch (Exception exc) {
			System.out.println("Error is : " + exc.toString());
		}

	}
}
