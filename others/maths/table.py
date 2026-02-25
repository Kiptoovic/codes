import speech_recognition as sr
import pyttsx3

# Initialize recognizer and text-to-speech engine
recognizer = sr.Recognizer()
engine = pyttsx3.init()

def ask_question(question):
    """Function to speak a question using text-to-speech"""
    try:
        engine.say(question)
        engine.runAndWait()
    except Exception as e:
        print(f"Error in speech synthesis: {e}")

def get_answer():
    """Function to capture and recognize speech input"""
    try:
        with sr.Microphone() as source:
            print("Adjusting for ambient noise...")
            recognizer.adjust_for_ambient_noise(source, duration=1)
            print("Listening for your answer...")
            audio = recognizer.listen(source, timeout=5)
            
            try:
                return recognizer.recognize_google(audio)
            except sr.UnknownValueError:
                return "Sorry, I did not understand that."
            except sr.RequestError:
                return "Sorry, my speech service is unavailable."
                
    except sr.WaitTimeoutError:
        return "No speech detected within the timeout period."
    except Exception as e:
        return f"An error occurred: {e}"

# Example usage
if _name_ == "_main_":
    question = "What is five times three?"
    ask_question(question)
    answer = get_answer()
    print(f"System received: {answer}")