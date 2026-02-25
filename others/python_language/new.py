import pandas as pd
import numpy as np

# Load sample data into a pandas DataFrame

sample_data = [{"order_id": 1, "customer_id": 4174.0, "city": "Thika", "product_category": "Groceries", "product_price": 63674.0, "discount": 0.0, "quantity": 3.0, "payment_method": "Card", "delivery_status": "Delivered", "delivery_time_days": 14.0, "seller_rating": 4.0, "customer_rating": 5.0, "return_reason": np.nan, "seller_id": 285.0, "rider_id": np.nan, "rider_delivery_success_rate": np.nan, "warehouse_id": 19.0, "warehouse_stock_level": np.nan, "support_ticket_opened": 1.0, "support_category": "Payment Issue", "marketing_campaign": "Social Media Ads", "campaign_conversion_rate": 0.1379332696227307}, {"order_id": 2, "customer_id": 4507.0, "city": "Nairobi", "product_category": "Beauty", "product_price": 68544.0, "discount": 15.0, "quantity": 3.0, "payment_method": "Airtel Money", "delivery_status": np.nan, "delivery_time_days": 8.0, "seller_rating": 5.0, "customer_rating": np.nan, "return_reason": np.nan, "seller_id": 261.0, "rider_id": 595.0, "rider_delivery_success_rate": np.nan, "warehouse_id": 18.0, "warehouse_stock_level": 357.0, "support_ticket_opened": 1.0, "support_category": "Product Issue", "marketing_campaign": np.nan, "campaign_conversion_rate": 0.1615706508822784}, {"order_id": 3, "customer_id": 1860.0, "city": "Kisumu", "product_category": "Groceries", "product_price": np.nan, "discount": 20.0, "quantity": 2.0, "payment_method": "Airtel Money", "delivery_status": "Delivered", "delivery_time_days": np.nan, "seller_rating": np.nan, "customer_rating": 1.0, "return_reason": np.nan, "seller_id": 241.0, "rider_id": 561.0, "rider_delivery_success_rate": 0.877710792305588, "warehouse_id": 15.0, "warehouse_stock_level": 248.0, "support_ticket_opened": 0.0, "support_category": "Payment Issue", "marketing_campaign": "Flash Sale", "campaign_conversion_rate": 0.1403057066774386}]

def generate_analytics():
    df = pd.DataFrame(sample_data)

    # Challenge1: Group by product_category and payment_method and calculate mean discount

grouped_discount = (
        df
        .groupby(['product_category', 'payment_method'], dropna=False)['discount']
        .mean()
        .reset_index()
    )
    # Challenge2: Pivot the table so that payment methods are columns and product categories are rows
    # Fill here ...
    pivoted_discount = grouped_discount.pivot_table(
        index='product_category', 
        columns='payment_method', 
        values='discount', 
        fill_value=0
    )

    # For analysis, print the pivoted table
    print(pivoted_discount)


