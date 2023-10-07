import javax.swing.JFrame;

class Client {

	public static void main(String[] args) {

		Gui bucky = new Gui(); // Here we call the GUI constructor
		bucky.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // The 'X' on the top right of gui frame will close it.
		bucky.setSize(500, 200); // Dimensions for GUI
		bucky.setVisible(true);
	}
}
