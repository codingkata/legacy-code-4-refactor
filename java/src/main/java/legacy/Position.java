package legacy;

public class Position {

	private int x;
	private int y;

	public Position(String x, String y) {
		this.x = Integer.parseInt(x);
		this.y = Integer.parseInt(y);
	}

	public void setX(int _x) {
		this.x = _x;
	}

	public int getX() {
		return this.x;
	}

	public void setY(int _y) {
		this.y = _y;
	}

	public int getY() {
		return this.y;
	}

	@Override
	public String toString() {
		return x + " " + y;
	}
}