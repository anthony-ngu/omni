typedef enum {
    MENU_ARRAY, // 0
	OPTION_ARRAY, // 1
	INT_RANGE // 2
} OptionType;

class MenuItem
{
    public:
        String headerText;
        String selectionText = "";
        OptionType optionType;
        
        int selectedIndex;
        
        // MENU_ARRAY
        MenuItem* children;
        int childrenLength;
        
        // OPTION_ARRAY
        String* options;
        int optionLength;
        
        // INT_RANGE
        int min;
        int max;
        int step;
        int count;
        
        MenuItem* parent;
        
    MenuItem(){}
    
    MenuItem(
        String inHeaderText,
        MenuItem inChildren[],
        int inChildrenLength)
    {
        // defaults
        optionType = MENU_ARRAY;
        selectedIndex = 0;
        
        // inputs
        headerText = inHeaderText;
        children = inChildren;
        childrenLength = inChildrenLength;
        
        // calculated
        selectionText = children[selectedIndex].headerText;
    }
    
    MenuItem(
        String inHeaderText,
        String* inOptions,
        int inOptionLength)
    {
        // defaults
        optionType = OPTION_ARRAY;
        selectedIndex = 0;
        
        // inputs
        headerText = inHeaderText;
        options = inOptions;
        optionLength = inOptionLength;
        
        // calculated
        selectionText = options[selectedIndex];
    }
    
    MenuItem(
        String inHeaderText,
        int inMin,
        int inMax,
        int inStep)
    {
        // defaults
        optionType = INT_RANGE;
        
        // inputs
        headerText = inHeaderText;
        min = inMin;
        max = inMax;
        step = inStep;
        
        // calculated
        count = (max+min)/2;
        selectionText = String(count);
    }
    
    void increment(){
        switch(optionType)
        {
            case MENU_ARRAY:
                if(++selectedIndex >= childrenLength) selectedIndex = childrenLength-1;
                selectionText = children[selectedIndex].headerText;
                break;
            case OPTION_ARRAY:
                if(++selectedIndex >= optionLength) selectedIndex = optionLength-1;
                selectionText = options[selectedIndex];
                break;
            case INT_RANGE:
                count += step;
                if(count > max) count = max;
                selectionText = String(count);
                break;    
            default:
                break;
        }
    }
    
    void decrement(){
        switch(optionType)
        {
            case MENU_ARRAY:
                if(--selectedIndex < 0) selectedIndex = 0;
                selectionText = children[selectedIndex].headerText;
                break;
            case OPTION_ARRAY:
                if(--selectedIndex < 0 ) selectedIndex = 0;
                selectionText = options[selectedIndex];
                break;
            case INT_RANGE:
                count -= step;
                if(count < min) count = min;
                selectionText = String(count);
                break;    
            default:
                break;
        }
    }
    
    void chooseSelection()
    {
        switch(optionType)
        {
            case MENU_ARRAY:
                // if(--selectedIndex < 0) selectedIndex = 0;
                // selectionText = children[selectedIndex].headerText;
                break;
            case OPTION_ARRAY:
                // if(--selectedIndex < 0 ) selectedIndex = 0;
                // selectionText = options[selectedIndex];
                break;
            case INT_RANGE:
                Particle.publish("call", headerText+":"+selectionText);
                break;    
            default:
                break;
        }
    }
};