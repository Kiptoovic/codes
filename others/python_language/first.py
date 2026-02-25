import SEO_Perfomance_Data_sheet1.csv as pd
import numpy as np
from datetime import datetime
from decimal import Decimal

# ==== Helper Functions (MANDATORY FULL IMPLEMENTATIONS) ====

def convert_columns(df):
    '''
    Convert datetime and numeric columns to appropriate data types.
    
    Args:
        df: DataFrame to process
        
    Returns:
        Processed DataFrame
    '''
    # Extract datetime and numeric columns within the function
    datetime_columns = [col for col in df.columns if 'date' in col.lower() or 'time' in col.lower()]
    numeric_columns = df.select_dtypes(include=['number']).columns.tolist()
    
    # Convert datetime columns
    for column in datetime_columns:
        if column in df.columns:
            df[column] = pd.to_datetime(df[column], errors='coerce')
    
    # Convert numeric columns and fill null with 0
    for column in numeric_columns:
        if column in df.columns:
            df[column] = pd.to_numeric(df[column], errors='coerce').fillna(0)

    return df

def safe_idxmax(series, default='Unknown'):
    '''
    Safely get the index of maximum value, with proper error handling.
    
    Args:
        series: Pandas Series to process
        default: Default value to return if operation fails
    
    Returns:
        Index of maximum value or default value
    '''
    # Handle empty series
    if series.empty:
        return default
        
    # Handle non-numeric series
    if not pd.api.types.is_numeric_dtype(series):
        try:
            series = pd.to_numeric(series, errors='coerce')
        except:
            return default
    
    # Handle all-null series
    if series.isna().all():
        return default
        
    try:
        return series.idxmax()
    except Exception:
        return default

def safe_idxmin(series, default='Unknown'):
    '''
    Safely get the index of minimum value, with proper error handling.
    
    Args:
        series: Pandas Series to process
        default: Default value to return if operation fails
    
    Returns:
        Index of minimum value or default value
    '''
    # Handle empty series
    if series.empty:
        return default
        
    # Handle non-numeric series
    if not pd.api.types.is_numeric_dtype(series):
        try:
            series = pd.to_numeric(series, errors='coerce')
        except:
            return default
    
    # Handle all-null series
    if series.isna().all():
        return default
        
    try:
        return series.idxmin()
    except Exception:
        return default

def prepare_for_json(value):
    '''
    Convert Python/NumPy types to JSON-serializable Python types.
    
    Args:
        value: Value to convert
    
    Returns:
        JSON-serializable value
    '''
    if isinstance(value, (np.int64, np.int32, np.int16, np.int8)):
        return int(value)
    if isinstance(value, (np.float64, np.float32, np.float16)):
        return float(value)
    if isinstance(value, (pd.Timestamp, datetime)):
        return value.isoformat()
    if isinstance(value, np.bool_):
        return bool(value)
    if isinstance(value, Decimal):
        return float(value) if value % 1 != 0 else int(value)
    if pd.isna(value):
        return None
    return value

def prepare_dict_for_json(d):
    '''
    Recursively convert dictionary values to JSON-serializable types.
    
    Args:
        d: Dictionary to process
    
    Returns:
        Dictionary with JSON-serializable values
    '''
    if not isinstance(d, dict):
        return prepare_for_json(d)
    
    result = {}
    for k, v in d.items():
        if isinstance(v, dict):
            result[k] = prepare_dict_for_json(v)
        elif isinstance(v, (list, tuple)):
            result[k] = [prepare_dict_for_json(i) if isinstance(i, dict) else prepare_for_json(i) for i in v]
        else:
            result[k] = prepare_for_json(v)
    return result

def prepare_list_for_json(lst):
    '''
    Recursively convert list values to JSON-serializable types.
    
    Args:
        lst: List to process
    
    Returns:
        List with JSON-serializable values
    '''
    result = []
    for item in lst:
        if isinstance(item, dict):
            result.append(prepare_dict_for_json(item))
        elif isinstance(item, (list, tuple)):
            result.append(prepare_list_for_json(item))
        else:
            result.append(prepare_for_json(item))
    return result

def round_numeric_values(value, decimal_places=2):
    '''
    Round numeric values to specified decimal places.
    
    Args:
        value: Value to round
        decimal_places: Number of decimal places
    
    Returns:
        Rounded value
    '''
    if isinstance(value, (int, float, np.number)) and not pd.isna(value):
        return round(float(value), decimal_places)
    return value

# ==== Main Analytics Function ====

def generate_analytics(input_data):
    '''
    Process file data and generate analytics based on user requirements.
    
    Args:
        input_data: Dictionary where keys are file names and values are corresponding DataFrames
        
    Returns:
        Dictionary with analytics results
    '''
    # User query/context for messaging
    user_query = "SEO Performance Data - Sheet1: Comprehensive Data Dictionary and Column Definitions"
    results = {'type': 'string'}
    message = user_query
    supporting_data = {}
    charts = []
    tables = []
    numerical_data = {}
    
    # Safety check for empty input
    if not input_data:
        message = 'No file data available for analysis'
        results['value'] = {
            'message': message,
            'supporting_data': supporting_data,
            'charts': charts,
            'tables': tables,
            'numerical_data': numerical_data
        }
        return results
    
    # For each file in input_data
    for file_name, data in input_data.items():
        # Convert to DataFrame if needed
        if isinstance(data, list):
            df = pd.DataFrame(data)
        elif isinstance(data, pd.DataFrame):
            df = data
        else:
            continue

        # Skip empty DataFrames
        if df.empty:
            continue

        # Process the DataFrame
        df = convert_columns(df)

        # --- Data Dictionary Construction ---
        # List all columns and for each, provide:
        # - Column Name (exact)
        # - Description (clear, concise)
        # - Data Type (Date, String/Text, Integer, Float, Percentage, Currency, Categorical)
        # - Example(s): Value(s) from sample data

        # Build column metadata
        column_descriptions = {
            'Date': {
                'Description': 'Timestamp indicating the specific date and time of the data record',
                'Data Type': 'DateTime'
            },
            'Month': {
                'Description': 'Month name extracted from the Date',
                'Data Type': 'Categorical'
            },
            'Year': {
                'Description': 'Year extracted from the Date',
                'Data Type': 'Integer'
            },
            'Quarter': {
                'Description': 'Fiscal quarter designation based on the date',
                'Data Type': 'Categorical'
            },
            'Time Of Day': {
                'Description': 'Time segment categorizing the time (e.g., Morning, Afternoon, Night)',
                'Data Type': 'Categorical'
            },
            'Primary Keywords': {
                'Description': 'Main keyword phrase targeted in SEO campaign',
                'Data Type': 'Text/String'
            },
            'Secondary Keywords': {
                'Description': 'Secondary keyword phrases related to primary keyword',
                'Data Type': 'Text/String'
            },
            'Long-Tail Keywords': {
                'Description': 'More specific, longer keyword phrases',
                'Data Type': 'Text/String'
            },
            'Location': {
                'Description': 'Geographic location associated with traffic or campaign',
                'Data Type': 'Categorical'
            },
            'Social Media Source': {
                'Description': 'Social media platform driving traffic or engagement',
                'Data Type': 'Categorical'
            },
            'Media Type': {
                'Description': 'Type of media content used (e.g., Infographic, Image gallery)',
                'Data Type': 'Categorical'
            },
            'Device Type': {
                'Description': 'Type of device visitors use (Mobile, Tablet, Laptop, Desktop)',
                'Data Type': 'Categorical'
            },
            'Organic_Traffic': {
                'Description': 'Number of visits from organic search traffic',
                'Data Type': 'Integer'
            },
            'Keywords_Ranking': {
                'Description': 'Number of ranked keywords or ranking score',
                'Data Type': 'Integer'
            },
            'Clicks': {
                'Description': 'Number of clicks from search results or campaigns',
                'Data Type': 'Integer'
            },
            'Impressions': {
                'Description': 'Number of times content appeared in search results or ads',
                'Data Type': 'Integer'
            },
            'CTR (%)': {
                'Description': 'Click Through Rate percentage (Clicks / Impressions * 100)',
                'Data Type': 'Percentage'
            },
            'Average_Position': {
                'Description': 'Average search engine result page position for keywords',
                'Data Type': 'Float'
            },
            'Backlinks': {
                'Description': 'Number of backlinks pointing to the site or page',
                'Data Type': 'Integer'
            },
            'Domain_Authority': {
                'Description': 'SEO metric representing domain strength (often scale 0-100)',
                'Data Type': 'Integer'
            },
            'Bounce_Rate (%)': {
                'Description': 'Percentage of sessions where users left after one page',
                'Data Type': 'Percentage'
            },
            'Pages_per_Session': {
                'Description': 'Average number of pages viewed per session',
                'Data Type': 'Float'
            },
            'Organic_vs_Paid_Traffic_Split (%)': {
                'Description': 'Percentage split between organic and paid traffic; typically proportion of organic traffic',
                'Data Type': 'Percentage'
            },
            'Organic_Traffic_Growth_Rate (%)': {
                'Description': 'Growth rate percentage of organic traffic compared to a previous period',
                'Data Type': 'Percentage'
            },
            'Conversion_Rate (%)': {
                'Description': 'Percentage of visitors completing desired actions (e.g., purchases, signups)',
                'Data Type': 'Percentage'
            },
            'Goal_Completions': {
                'Description': 'Absolute count of goal completions (e.g., sales, leads)',
                'Data Type': 'Integer'
            },
            'Average_Session_Duration (sec)': {
                'Description': 'Average duration of a user session in seconds',
                'Data Type': 'Integer'
            },
            'New_vs_Returning_Visitors (%)': {
                'Description': 'Percentage split between new and returning visitors',
                'Data Type': 'Percentage'
            },
            'Exit_Rate (%)': {
                'Description': 'Percentage of exits from a page relative to total pageviews',
                'Data Type': 'Percentage'
            },
            'Top_Landing_Pages': {
                'Description': 'Most frequent landing pages for visitors',
                'Data Type': 'Categorical/Text'
            },
            'Keyword_Difficulty': {
                'Description': 'SEO metric indicating how difficult it is to rank for the keyword',
                'Data Type': 'Float'
            },
            'CPC_for_Paid_Keywords ($)': {
                'Description': 'Cost-Per-Click in USD for paid keywords',
                'Data Type': 'Currency (Float)'
            },
            'Indexed_Pages': {
                'Description': 'Number of pages indexed by search engines',
                'Data Type': 'Integer'
            },
            'Mobile_vs_Desktop_Traffic_Split (%)': {
                'Description': 'Percentage traffic from mobile devices vs desktop',
                'Data Type': 'Percentage'
            },
            'Organic_Revenue ($)': {
                'Description': 'Revenue generated from organic traffic, in USD',
                'Data Type': 'Currency (Float)'
            },
            'Page_Load_Time (sec)': {
                'Description': 'Average page load time in seconds',
                'Data Type': 'Float'
            },
            'Core_Web_Vitals_LCP (sec)': {
                'Description': 'Largest Contentful Paint metric — time to load largest visible content',
                'Data Type': 'Float'
            },
            'Core_Web_Vitals_FID (ms)': {
                'Description': 'First Input Delay metric — time from user interaction to browser response',
                'Data Type': 'Float (ms)'
            },
            'Core_Web_Vitals_CLS': {
                'Description': 'Cumulative Layout Shift metric — measure of visual stability',
                'Data Type': 'Float'
            },
            'Social_Shares': {
                'Description': 'Number of times content was shared on social media',
                'Data Type': 'Integer'
            },
            'Referral_Traffic': {
                'Description': 'Number of visits coming from referral sources (other websites)',
                'Data Type': 'Integer'
            },
            'Technical_SEO_Errors': {
                'Description': 'Count of technical SEO issues detected',
                'Data Type': 'Integer'
            },
            'Bounce_Rate_by_Device_Mobile (%)': {
                'Description': 'Bounce rate specifically for mobile device sessions',
                'Data Type': 'Percentage'
            },
            'Time_to_First_Byte_TTFB (ms)': {
                'Description': 'Time to First Byte metric — server responsiveness time in milliseconds',
                'Data Type': 'Integer (ms)'
            }
        }

        # Prepare column metadata table
        table_rows = []
        for col in df.columns:
            desc = column_descriptions.get(col, {})
            # Data type fallback
            data_type = desc.get('Data Type', str(df[col].dtype))
            # Description fallback
            description = desc.get('Description', '')
            # Example(s): First non-null value or None
            eg_value = None
            # Get up to 2 unique examples, excluding NaNs
            unique_vals = df[col].dropna().unique()
            if len(unique_vals) == 0:
                eg_value = None
            elif len(unique_vals) == 1:
                eg_value = unique_vals[0]
            else:
                eg_value = [unique_vals[0], unique_vals[1]]
            # If value is numpy type, convert for JSON
            eg_value = prepare_for_json(eg_value)
            # Row dict
            row = {
                "Column Name": col,
                "Description": description,
                "Data Type": data_type,
                "Example(s)": eg_value
            }
            table_rows.append(row)

        # Table object as per requirements
        table_obj = {
            'id': 'table-0',
            'name': f"Data Dictionary for '{file_name}'",
            'data': table_rows,
            'summary_data_points': {
                'total_columns': len(df.columns),
                'columns_with_examples': sum(1 for r in table_rows if r.get('Example(s)') is not None),
                'categorical_columns': sum(1 for r in table_rows if 'Categorical' in str(r.get('Data Type', ''))),
                'numeric_columns': sum(1 for r in table_rows if any(x in str(r.get('Data Type', '')).lower() for x in ['integer', 'float', 'currency', 'percentage'])),
                'text_columns': sum(1 for r in table_rows if 'Text' in str(r.get('Data Type', '')) or 'String' in str(r.get('Data Type', '')))
            }
        }

        tables.append(table_obj)

        # No charts, as per instructions
        # No numerical_data required for this query (it's about metadata)
        numerical_data = {}

        # No supporting_data needed (could add column counts, etc., but not required)

        # Only process one file for this query (single sheet)

    # Format and sanitize results
    if supporting_data:
        supporting_data = prepare_dict_for_json(supporting_data)
    if numerical_data:
        numerical_data = prepare_dict_for_json(numerical_data)
    if charts:
        charts = prepare_list_for_json(charts)
    if tables:
        tables = prepare_list_for_json(tables)

    results['value'] = {
        'message': message,
        'supporting_data': supporting_data,
        'charts': charts,
        'tables': tables,
        'numerical_data': numerical_data
    }
    return results