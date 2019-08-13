package legacy;

public class Detector {
	private Position pos;
	private char faceTo;
	private String moveCmd;
	private Position MaxPosition;

	public Detector(char faceTo, Position pos, String cmd , Position MaxPosition) {
		this.pos = pos;
		this.faceTo = faceTo;
		this.moveCmd = cmd;
		this.MaxPosition = MaxPosition;
	}

	public void excuteCMD(Direction direction) {
		String cmd = this.getMoveCmd();
		char[] cmd_array = cmd.toUpperCase().toCharArray();
		for (int i = 0; i < cmd_array.length; i++) {
			if (cmd_array[i] == 'M') {
				this.pos = direction.moveXY(this.faceTo, this.pos);
			} else {
				this.faceTo = direction.turnTo(this.faceTo,
						String.valueOf(cmd_array[i]));
			}
		}
	}

	@Override
	public String toString() {
		if(pos.getX() == MaxPosition.getX() || pos.getY() == MaxPosition.getY()){
			return pos + " " + faceTo  +  " " + "RIP"  + "\n";
		}
		return pos + " " + faceTo + "\n";
	}

	public String getMoveCmd() {
		return moveCmd;
	}

	public void setMoveCmd(String moveCmd) {
		this.moveCmd = moveCmd;
	}

	public char getFaceTo() {
		return faceTo;
	}

	public void setFaceTo(char faceTo) {
		this.faceTo = faceTo;
	}

	public void setPos(Position _pos) {
		this.pos = _pos;
	}

	public Position getPos() {
		return this.pos;
	}

}