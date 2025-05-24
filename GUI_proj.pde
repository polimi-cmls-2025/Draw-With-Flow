import oscP5.*;
import netP5.*;
import processing.serial.*;

OscP5 oscP5;
NetAddress superCollider;
Serial myPort;

Knob moodSelector;
Knob[] knobs = new Knob[4];
ToggleButton effectButton;
Knob activeKnob = null;

float[] moodAngles = { radians(180), radians(270), radians(0), radians(90) };
String[] moodNames = { "angry", "chill", "happy", "sad" };

int lastBPMValue = -1;
int lastSentBPM = -1;

float lastSpeedNorm = 0;

color OVERDRIVE_COLOUR = #AE3731;
color REVERB_COLOUR    = #C548B0;
color CHORUS_COLOUR    = #49ACC8;
color DELAY_COLOUR     = #7AC548;
color KNOB_COLOUR      = #3E3E3E;
color POINTER_COLOUR   = #D4D4D6;
color GRAY_COLOUR      = #8E8E8E;
                        
PFont font;

void serialEvent(Serial myPort) {
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    inString = trim(inString);

    if (inString.startsWith("BPM:")) {
      try {
        lastBPMValue = int(trim(inString.substring(4)));
      } catch (Exception e) {
      }

    } else if (inString.startsWith("SPEED_AVG_NORM:")) {
      try {
        lastSpeedNorm = float(trim(inString.substring(15)));
        if (lastSpeedNorm > 0.3) {
          lastSpeedNorm += 0.3;
          if (lastSpeedNorm > 1) 
            lastSpeedNorm = 1;
        }
      } catch (Exception e) {
      }
    }
  }
}

void setup() {
  size(936, 768);
  
  font = createFont("rajdhani",13);
  
  String portName = "/dev/tty.usbmodem21401"; 
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
  
  oscP5 = new OscP5(this, 12000); 
  superCollider = new NetAddress("127.0.0.1", 57120);
  
  moodSelector = new Knob(234, height/2, 90, "", true);

  float baseX = 620;
  float spacingX = 170;
  float spacingY = 170;
  float topY = 300;

  knobs[0] = new Knob(baseX, topY, 60, "Param 1", false);
  knobs[1] = new Knob(baseX + spacingX, topY, 60, "Param 2", false);
  knobs[2] = new Knob(baseX, topY + spacingY, 60, "Param 3", false);
  knobs[3] = new Knob(baseX + spacingX, topY + spacingY, 60, "Param 4", false);

  effectButton = new ToggleButton(baseX + spacingX / 2 - 60, topY + spacingY * 2 + 20, 120, 40, "CHORUS");
  
  pixelDensity(displayDensity());
}

void sendParameterChange(String paramName, float value) {
  OscMessage msg = new OscMessage("/set" + paramName);
  msg.add(value);
  oscP5.send(msg, superCollider);
}

float mapWithSkew(float norm, float floor, float ceil, float skew) {
    return floor + pow(norm, skew) * (ceil - floor);
}

void setKnobValuesForMood(String mood) {
  if (mood.equals("angry")) {
    knobs[0].angle = map(0.5, 0, 1, -PI/2, PI/2); // esempio Gain a 0.5 norm
    knobs[1].angle = map(0.5625, 0, 1, -PI/2, PI/2); // Tone
    knobs[2].angle = map(0.31510880589485, 0, 1, -PI/2, PI/2); // Output Level
    knobs[3].angle = -PI/2; // knob vuoto, angolo minimo (o 0)
  } else if (mood.equals("chill")) {
    knobs[0].angle = map(0.6700000166893, 0, 1, -PI/2, PI/2); // Room Size
    knobs[1].angle = map(0.34999999403954, 0, 1, -PI/2, PI/2); // Damping
    knobs[2].angle = map(1.0, 0, 1, -PI/2, PI/2); // Width
    knobs[3].angle = map(0.31999999284744, 0, 1, -PI/2, PI/2); // Reverb Dry/Wet
  } else if (mood.equals("happy")) {
    knobs[0].angle = map(0.49323096871376, 0, 1, -PI/2, PI/2); // Rate
    knobs[1].angle = map(0.60310226678848, 0, 1, -PI/2, PI/2); // Intensity (nota che è 0-100)
    knobs[2].angle = map(0.44999998807907, 0, 1, -PI/2, PI/2); // Amount
    knobs[3].angle = map(1.0, 0, 1, -PI/2, PI/2); // Stereo Width
  } else if (mood.equals("sad")) {
    knobs[0].angle = map(0.61193478107452, 0, 1, -PI/2, PI/2); // Delay Time
    knobs[1].angle = map(0.08500000089407, 0, 1, -PI/2, PI/2); // Feedback
    knobs[2].angle = map(0.34999999403954, 0, 1, -PI/2, PI/2); // Delay Dry/Wet
    knobs[3].angle = -PI/2; // knob vuoto
  }
  
  effectButton.state = true;
}

void draw() {
  background(240);
  
  textFont(font);
  
  float leftCenter = width / 4;
  textAlign(CENTER, TOP);
  textSize(36);
  fill(0);
  text("Mood", leftCenter - 20, 50);
  String mood = getMood(moodSelector.angle);  
  color fxColor = getMoodColor(mood);
  fill(fxColor);
  text("  FX", leftCenter + 30, 50);
  fill(0);
  textSize(16);
  text("by BIME", leftCenter + 5, 90);


  float rightCenter = 3 * width / 4;
  textAlign(CENTER, TOP);
  textSize(20);
  fill(0);
  text("EFFECT SETUP", rightCenter, 55);


  stroke(180);
  noFill();
  rect(10, 10, width - 20, height - 20, 20);
  line(width/2, 10, width/2, height - 10);

  updateKnobLabels(mood);
  moodSelector.displayMoodSelector();

  drawMoodLabels();

  fill(0);
  textAlign(CENTER, CENTER);
  textSize(14);
  text("Let your mood choose the sound.", width/4, height - 85);

  int numKnobsToShow = (mood.equals("angry") || mood.equals("sad")) ? 3 : 4;
  

  if (mood.equals("angry") || mood.equals("sad")) {
    float centerX = (knobs[0].x + knobs[1].x) / 2;
    knobs[2].x = centerX;
  } else {
    knobs[2].x = knobs[0].x;
  }

  for (int i = 0; i < numKnobsToShow; i++) {
    knobs[i].displayEffectKnob();
  }

  effectButton.label = getEffectName(mood);
  effectButton.display();
  
  fill(0);
  textAlign(CENTER, CENTER);
  textSize(18);
  text("MOOD SELECTOR", width/4, height - 190);
 

  if (lastBPMValue != -1 && lastBPMValue != lastSentBPM) {
    OscMessage bpmMsg = new OscMessage("/setBpm");
    bpmMsg.add((float)lastBPMValue);
    oscP5.send(bpmMsg, superCollider);
    lastSentBPM = lastBPMValue;
    
    if (mood.equals("sad")) {
      float delayTime = lastSentBPM / 60.0;
      
      float minVal = 0.05;
      float maxVal = 5.0;
      float skew = 0.4;
      
      float norm = pow(((delayTime - minVal) / (maxVal - minVal)), skew);
      knobs[0].angle = map(norm, 0.0, 1.0, -HALF_PI, HALF_PI);
      float valueToSend = map(knobs[0].getMappedValue(), 0.0, 100.0, 0.0, 1.0);
      sendParameterChange("DelayTime", valueToSend);
    }
    
  }
  
  if (mood.equals("angry")) {
    knobs[0].angle = map(lastSpeedNorm, 0.0, 1.0, -HALF_PI, HALF_PI);
    float gainValue = knobs[0].getMappedValue();
    sendParameterChange("Gain", gainValue);
  } else if (mood.equals("chill")) {
    knobs[0].angle = map(lastSpeedNorm, 0.0, 1.0, -HALF_PI, HALF_PI);
    float rmSizeValue = map(knobs[0].getMappedValue(), 0.0, 100.0, 0.0, 1.0);
    sendParameterChange("RoomSize", rmSizeValue);
  } else if (mood.equals("sad")) {
    knobs[1].angle = map(lastSpeedNorm, 0.0, 1.0, -HALF_PI, HALF_PI);
    float feedbackValue = map(knobs[1].getMappedValue(), 0.0, 100.0, 0.0, 1.0);
    sendParameterChange("Feedback", feedbackValue);
  } else if (mood.equals("happy")) {
    knobs[1].angle = map(lastSpeedNorm, 0.0, 1.0, -HALF_PI, HALF_PI);
    float intensityValue = map(knobs[1].getMappedValue(), 0.0, 100.0, 0.0, 1.0);
    sendParameterChange("Intensity", intensityValue);
  }
}

void mousePressed() {
  moodSelector.checkClick(mouseX, mouseY);
  for (Knob k : knobs) k.checkClick(mouseX, mouseY);
  effectButton.checkClick(mouseX, mouseY);
}

void mouseDragged() {
  if (activeKnob != null) {
     activeKnob.updateAngle(mouseX, mouseY);
     
  if (!activeKnob.isMoodSelector) {
  activeKnob.updateAngle(mouseX, mouseY);
  
  float valueToSend;

  if (activeKnob.label.equals("Rate (Hz)")) {
    float rateValue = activeKnob.getMappedValue();
    sendParameterChange("Rate", rateValue);
  } else if (activeKnob.label.equals("Delay Time")) {
      float delayTimeValue = activeKnob.getMappedValue();
      sendParameterChange("DelayTime", delayTimeValue);
  } else if (activeKnob.label.equals("Gain")) {
      float gainValue = activeKnob.getMappedValue();
      sendParameterChange("Gain", gainValue);
  } else if (activeKnob.label.equals("Tone")) {
      float toneValue = activeKnob.getMappedValue();
      sendParameterChange("Tone", toneValue);
  } else if (activeKnob.label.equals("Output Level")) {
      float outLvlValue = activeKnob.getMappedValue();
      sendParameterChange("OutputLevel", outLvlValue);
  } else if (activeKnob.label.equals("Stereo Width")) {
      valueToSend = map(activeKnob.angle, -HALF_PI, HALF_PI, 0.0, 1.0);
      sendParameterChange("StereoWidth", valueToSend);
  } else if (activeKnob.label.equals("Intensity")) {
      valueToSend = map(activeKnob.angle, -HALF_PI, HALF_PI, 0.0, 1.0);
      sendParameterChange("Intensity", valueToSend);
  } else if (activeKnob.label.equals("Amount")) {
      valueToSend = map(activeKnob.angle, -HALF_PI, HALF_PI, 0.0, 1.0);
      sendParameterChange("Amount", valueToSend);
  } else if (activeKnob.label.equals("Room Size")) {
      valueToSend = map(activeKnob.angle, -HALF_PI, HALF_PI, 0.0, 1.0);
      sendParameterChange("RoomSize", valueToSend);
  } else if (activeKnob.label.equals("Damping")) {
      valueToSend = map(activeKnob.angle, -HALF_PI, HALF_PI, 0.0, 1.0);
      sendParameterChange("Damping", valueToSend);
  } else if (activeKnob.label.equals("Width")) {
      valueToSend = map(activeKnob.angle, -HALF_PI, HALF_PI, 0.0, 1.0);
      sendParameterChange("Width", valueToSend);
  } else if (activeKnob.label.equals("Reverb Dry/Wet")) {
      valueToSend = map(activeKnob.angle, -HALF_PI, HALF_PI, 0.0, 1.0);
      sendParameterChange("ReverbDw", valueToSend);
  } else if (activeKnob.label.equals("Feedback")) {
      valueToSend = map(activeKnob.angle, -HALF_PI, HALF_PI, 0.0, 1.0);
      sendParameterChange("Feedback", valueToSend);
  } else if (activeKnob.label.equals("Delay Dry/Wet")) {
      valueToSend = map(activeKnob.angle, -HALF_PI, HALF_PI, 0.0, 1.0);
      sendParameterChange("DelayDw", valueToSend);
  }
  }
  }
}

void mouseReleased() {
  if (activeKnob != null && activeKnob.isMoodSelector) {
    float dx = mouseX - activeKnob.x;
    float dy = mouseY - activeKnob.y;
    float angleMouse = degrees(atan2(dy, dx));
    if (angleMouse < 0) angleMouse += 360;
    
    if (angleMouse >= 315 || angleMouse < 45) activeKnob.angle = radians(0);    // happy
    else if (angleMouse >= 45 && angleMouse < 135) activeKnob.angle = radians(90);  // sad
    else if (angleMouse >= 135 && angleMouse < 225) activeKnob.angle = radians(180); // angry
    else activeKnob.angle = radians(270);   // chill
    
    String mood = getMood(moodSelector.angle);
    OscMessage moodMsg = new OscMessage("/mood");
    moodMsg.add(mood);
    oscP5.send(moodMsg, superCollider);
    
    
    // GUI update
    setKnobValuesForMood(mood);
  }
  activeKnob = null;
}

// ----------------- Utility -----------------
color getMoodColor(String mood) {
  if (mood.equals("angry")) return OVERDRIVE_COLOUR;
  if (mood.equals("chill")) return REVERB_COLOUR;
  if (mood.equals("happy")) return DELAY_COLOUR;
  if (mood.equals("sad")) return CHORUS_COLOUR;
  return GRAY_COLOUR;
}

String getEffectName(String mood) {
  if (mood.equals("angry")) return "OVERDRIVE";
  if (mood.equals("chill")) return "REVERB";
  if (mood.equals("happy")) return "CHORUS";
  if (mood.equals("sad")) return "DELAY";
  return "EFFECT";
}

// ----------------- Classes -----------------

class Knob {
  float x, y, radius, angle;
  String label;
  boolean isMoodSelector;

  Knob(float x, float y, float r, String label, boolean isMoodSelector) {
    this.x = x;
    this.y = y;
    this.radius = r;
    this.label = label;
    this.angle = 0;
    this.isMoodSelector = isMoodSelector;
  }

  void displayMoodSelector() {
  color c = getMoodColor(getMood(angle));
  stroke(c);
  strokeWeight(4);
  fill(220);
  ellipse(x, y, radius*2, radius*2);

  float pointerX = x + cos(angle) * radius * 0.75;
  float pointerY = y + sin(angle) * radius * 0.75;

  noStroke();
  fill(c);
  ellipse(pointerX, pointerY, 10, 10);

  fill(0);
  textAlign(CENTER);
  textSize(12);
  text(label, x, y + radius + 20);

  if (!isMoodSelector) {
    int value = int(map(angle, -PI/2, PI/2, -100, 100));
    text("Value: " + value, x, y + radius + 35);
  }
}


  float initialY;  

void checkClick(float mx, float my) {
  float d = dist(mx, my, x, y);
  if (d < radius) {
    activeKnob = this;
    initialY = my;  
  }
}

void updateAngle(float mx, float my) {
  if (isMoodSelector) {
 
    float dx = mx - x;
    float dy = my - y;
    angle = atan2(dy, dx);
  } else {

    float deltaY = initialY - my;  

    float sensitivity = 300.0;
    angle += (deltaY / sensitivity) * PI;

    angle = constrain(angle, -PI/2, PI/2);

    initialY = my;
  }
}

  void displayEffectKnob() {
    String mood = getMood(moodSelector.angle);
    color arcColor = getMoodColor(mood);

    float startAngle = radians(135);
    float endAngle = radians(405);
    float valueAngle = map(constrain(angle, -PI/2, PI/2), -PI/2, PI/2, startAngle, endAngle);

    noStroke();
    fill(KNOB_COLOUR);
    ellipse(x, y, radius * 2, radius * 2);

    stroke(GRAY_COLOUR);
    strokeWeight(5);
    noFill();
    arc(x, y, radius * 2, radius * 2, startAngle, endAngle);

    stroke(arcColor);
    arc(x, y, radius * 2, radius * 2, startAngle, valueAngle);

    float pointerX = x + cos(valueAngle) * radius * 0.75;
    float pointerY = y + sin(valueAngle) * radius * 0.75;
    noStroke();
    fill(255);
    ellipse(pointerX, pointerY, 5, 5);

    fill(0);
    textAlign(CENTER);
    textSize(12);
    text(label.toUpperCase(), x, y + radius + 20);
    textSize(13);
    float value = getMappedValue();
    textSize(13);
    if (label.equals("Rate (Hz)")) {
      float minVal = 0.1;
      float maxVal = 20.0;
      float skew = 0.4;
      float norm = getMappedValue();
      
      float real = minVal + (maxVal - minVal) * pow(norm, 1.0 / skew);
      
      text(nfc(real, 2) +  " Hz", x, y + radius + 35);
    } else if (label.equals("Delay Time")) {
      float minVal = 0.05;
      float maxVal = 5.0;
      float skew = 0.4;
      float norm = getMappedValue();
      
      float real = minVal + (maxVal - minVal) * pow(norm, 1.0 / skew);
      
      text(nfc(real, 2) +  " s", x, y + radius + 35);
    } else if (label.equals("Gain")) {
      float minVal = 0.0;
      float maxVal = 20.0;
      float skew = 1.0;
      float norm = getMappedValue();
      
      float real = minVal + (maxVal - minVal) * pow(norm, 1.0 / skew);
      
      text(nfc(real, 2) +  " dB", x, y + radius + 35);
    } else if (label.equals("Tone")) {
      float minVal = -12.0;
      float maxVal = 12.0;
      float skew = 1.0;
      float norm = getMappedValue();
      
      float real = minVal + (maxVal - minVal) * pow(norm, 1.0 / skew);
      
      text(nfc(real, 2) +  " dB", x, y + radius + 35);
    } else if (label.equals("Output Level")) {
      float minVal = -12.0;
      float maxVal = 6.0;
      float skew = 0.585;
      float norm = getMappedValue();
      
      float real = minVal + (maxVal - minVal) * pow(norm, 1.0 / skew);
      
      text(nfc(real, 2) +  " dB", x, y + radius + 35);
    } else {
      text(int(value), x, y + radius + 35);
    }
  }
  
  float getMappedValue() {
    if (label.equals("Rate (Hz)") || label.equals("Delay Time") || label.equals("Tone") || label.equals("Output Level") || label.equals("Gain")) {
      float norm = map(angle, -PI/2, PI/2, 0, 1);
      return norm;
    }

    return map(angle, -PI/2, PI/2, 0, 100);
  }
}

class ToggleButton {
  float x, y, w, h;
  boolean state = true;
  String label;

  ToggleButton(float x, float y, float w, float h, String label) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.label = label;
  }

  void display() {
    String mood = getMood(moodSelector.angle);
    stroke(0);
    fill(state ? getMoodColor(mood) : color(200));
    rect(x, y, w, h, 10);
    fill(0);
    textAlign(CENTER, CENTER);
    textSize(14);
    text(label, x + w/2, y + h/2);
  }

  void checkClick(float mx, float my) {
    if (mx > x && mx < x + w && my > y && my < y + h) state = !state;
    
    float valueToSend = 0.0;
    if (state)
      valueToSend = 1.0;

    if (label.equals("CHORUS"))
      sendParameterChange("ChorusStatus", valueToSend);
    else if (label.equals("OVERDRIVE"))
      sendParameterChange("OverdriveStatus", valueToSend);
    else if (label.equals("REVERB"))
      sendParameterChange("ReverbStatus", valueToSend);
    else if (label.equals("DELAY"))
      sendParameterChange("DelayStatus", valueToSend);      
  }
}

// ----------------- Mood Logic -----------------

String getMood(float angle) {
  float minDiff = TWO_PI;
  int closestIndex = 0;
  for (int i = 0; i < moodAngles.length; i++) {
    float diff = abs(angle - moodAngles[i]);
    if (diff < minDiff) {
      minDiff = diff;
      closestIndex = i;
    }
  }
  return moodNames[closestIndex];
}

void updateKnobLabels(String mood) {
  if (mood.equals("happy")) {
    knobs[0].label = "Rate (Hz)";
    knobs[1].label = "Intensity";
    knobs[2].label = "Amount";
    knobs[3].label = "Stereo Width";
  } else if (mood.equals("chill")) {
    knobs[0].label = "Room Size";
    knobs[1].label = "Damping";
    knobs[2].label = "Width";
    knobs[3].label = "Reverb Dry/Wet";
  } else if (mood.equals("angry")) {
    knobs[0].label = "Gain";
    knobs[1].label = "Tone";
    knobs[2].label = "Output Level";
    knobs[3].label = "";
  } else if (mood.equals("sad")) {
    knobs[0].label = "Delay Time";
    knobs[1].label = "Feedback";
    knobs[2].label = "Delay Dry/Wet";
    knobs[3].label = "";
  }
}    

// ----------------- Draw Mood Labels -----------------

void drawMoodLabels() {
  float cx = moodSelector.x;
  float cy = moodSelector.y;
  float r = moodSelector.radius + 40;

  fill(0);
  textAlign(CENTER, CENTER);
  textSize(14);
  text("CHILL", cx, cy - r + 6);
  text("HAPPY", cx + r, cy);
  text("ANGRY", cx - r, cy);
  text("SAD", cx, cy + r);
}
